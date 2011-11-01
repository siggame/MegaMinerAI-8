#!/usr/bin/env python
### Missouri S&T ACM SIG-Game Arena (Thunderdome)
#####

# Some magic to get a standalone python program hooked in to django
import sys
sys.path = ['/home/mies/mysite', '/home/mies/mysite/mysite/'] + sys.path

from django.core.management import setup_environ
import settings

setup_environ(settings)

# Non-Django 3rd Party Imports
from time import sleep
import beanstalkc
import random

# My Imports
from thunderdome.models import Client, Game, GameData, Match

def main():
    stalk = beanstalkc.Connection()
    stalk.watch('game-requests')
    championship = Match.objects.get(root=True)
    while championship.winner is None:
        maintain_bracket(championship)
        if stalk.stats_tube('game-requests')['current-jobs-ready'] < 1:
            generate_speculative_game(championship)
        sleep(2)
    

def generate_speculative_game(match):
    traverse = [match]
    clients = list()
    while len(traverse) > 0:
        match = traverse.pop(0)
        if match.status == 'Complete':
            clients.append( match.winner )
        if match.status == 'Waiting':
            if match.p0 is None:
                traverse.append(match.father)
            if match.p1 is None:
                traverse.append(match.mother)
        if match.status == 'Running':
            clients += [match.p0, match.p1]
    if len(clients) > 2:
        game = Game.objects.create()
        p0, p1 = random.sample(clients, 2)
        GameData(game=game, client=p0).save()
        GameData(game=game, client=p1).save()
        game.tournament = True
        game.claimed = False
        game.schedule()
        print "Speculatively scheduled", p0.name, "vs", p1.name
        
        
def maintain_bracket(match):
    ### do a breadth first search down the dependency tree, looking
    ### for solvable dependencies. except it's not a dependency tree.
    ### it's a tournament bracket. which is jock-speak for dependency tree.
    matchlist = list()
    matchlist.append(match)
    while len(matchlist) > 0:
        match = matchlist.pop(0)
        if match.status != 'Complete':
            if match.p0 is None:
                matchlist.append(match.father)
            if match.p1 is None:
                matchlist.append(match.mother)
            maintain_match(match)
            
            
def maintain_match(match):
    ### Check on a single match, get it going if possible

    # check if parent maintanence can get this match started
    if match.p0 is None and match.father is not None:
        if match.father_type == 'win' and match.father.winner is not None:
            match.p0 = match.father.winner
        if match.father_type == 'lose' and match.father.loser is not None:
            match.p0 = match.father.loser
            
    if match.p1 is None and match.mother is not None:
        if match.mother_type == 'win' and match.mother.winner is not None:
            match.p1 = match.mother.winner
        if match.mother_type == 'lose' and match.mother.loser is not None:
            match.p1 = match.mother.loser

    #  might have gotten one but not the other
    if match.p0 is None or match.p1 is None:
        match.save()
        return
    
    match.status = 'Running'
    p0wins = len(match.games.filter(winner=match.p0))
    p1wins = len(match.games.filter(winner=match.p1))
    if p0wins >= match.wins_to_win:
        match.winner = match.p0
        match.loser  = match.p1
        match.status = 'Complete'
        print "********", match.winner.name, "beats", match.loser.name
        match.save()
        return
    if p1wins >= match.wins_to_win:
        match.winner = match.p1
        match.loser  = match.p0
        match.status = 'Complete'
        print "********", match.winner.name, "beats", match.loser.name
        match.save()
        return

    # if we made it to here, we're making games. but, how many?
    # how about "enough to possibly finish, if the loser would
    # kindly stop winning"
    count = match.wins_to_win + min([p0wins,p1wins]) - len(match.games.all())
    for i in xrange(count):
        game = get_game_from_pool(match)
        if game is None:
            game = Game.objects.create()
            GameData(game=game, client=match.p0).save()
            GameData(game=game, client=match.p1).save()
            game.tournament = True
            game.schedule()
            print "Scheduled", match.p0.name, "vs", match.p1.name
        else:
            print "Got", match.p0.name, "vs", match.p1.name, "from pool"
            game.claimed = True
            game.save()
        match.games.add(game)
    match.save()


def get_game_from_pool(match):
    for game in list(Game.objects.filter(claimed=False)):
        gd = list(game.gamedata_set.all())
        if gd[0].client == match.p0 and gd[1].client == match.p1:
            return game
        if gd[0].client == match.p1 and gd[1].client == match.p0:
            return game
    return None
    

main()
