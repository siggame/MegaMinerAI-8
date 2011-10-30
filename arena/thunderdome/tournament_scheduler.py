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
import beanstalkc
import random
from time import sleep

# My Imports
from thunderdome.models import Client, Game, GameData, Match

def main():
    championship = Match.objects.get(root=True)
    while championship.winner is None:
        maintain_bracket(championship)
        sleep(1)
    

def maintain_bracket(match):
    if match.winner is not None: # match complete
        return
    
    # maintain parent matches if needed
    if match.p0 is None:
        maintain_bracket(match.father)
    if match.p1 is None:
        maintain_bracket(match.mother)
                                    
    # check if that parent maintanence can get this match started
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
        print match.winner.name, "wins the match!"
        match.save()
        return
    if p1wins >= match.wins_to_win:
        match.winner = match.p1
        match.loser  = match.p0
        match.status = 'Complete'
        print match.winner.name, "wins the match!"
        match.save()
        return

    if len(match.games.exclude(status='Complete')) > 0:
        return

    # if we made it to here, we're making games. but, how many?
    count = match.wins_to_win if len(match.games.all()) == 0 else 1
    for i in xrange(count):
        game = Game.objects.create()
        GameData(game=game, client=match.p0).save()
        GameData(game=game, client=match.p1).save()
        match.games.add(game)
        game.schedule()
        print "Scheduled", match.p0.name, "vs", match.p1.name
    
main()
