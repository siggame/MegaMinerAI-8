#!/usr/bin/env python
### Missouri S&T ACM SIG-Game Arena (Thunderdome)
#####

# My AWS credentials
from aws_creds import access_cred, secret_cred

# Some magic to get a standalone python program hooked in to django
import sys
sys.path = ['/home/mnuck/', '/home/mnuck/django_dev_site'] + sys.path

from django.core.management import setup_environ
from django_dev_site import settings

setup_environ(settings)

# Non-Django 3rd Part Imports
import beanstalkc
import json
import git
import shutil
import subprocess
import random
import time
import os
import boto

# My Imports
from thunderdome.models import Game

def main():
    while True:
        looping()

def looping():
    # get a game
    stalk = beanstalkc.Connection()
    stalk.watch('game-requests')
    job = stalk.reserve()
    job_bits = json.loads(job.body)
    game_id = job_bits['game_id']
    game = Game.objects.get(pk=game_id)

    gamedatas = list(game.gamedata_set.all())
    random.shuffle(gamedatas)

    # handle embargoed players
    if any([x.client.embargoed for x in gamedatas]):
        game.status = "Failed"
        game.save()
        print "failing the game, embargoed player"
        return
    
    # get and compile the clients
    trash = open("/dev/null", 'w')
    for x in gamedatas:
        # handle embargoed
        update_local_repo(x.client.name)
        result = subprocess.call(['make'], cwd=x.client.name, 
                                 stdout=trash, stderr=trash)
        x.compiled = (result is 0)
        if not x.compiled:
            x.client.embargoed = True
            x.client.save()
        x.save()
        print "result for make in %s was %s" % (x.client.name, x.compiled)

    # handle a failed game
    if not all([x.compiled for x in gamedatas]):
        game.status = "Failed"
        game.save()
        print "failing the game"
        trash.close()
        return
    
    # prep for the game
    get_fresh_server()    
    server = subprocess.Popen(['python', 'main.py'], 
                              cwd='server',
                              stderr=trash)
    time.sleep(2)

    # FIXME some day the server will allow me to connect everyone
    # to a game of my choice. and then this can be de-uglified
    executable = '%s/%s/run' % (os.getcwd(), gamedatas[0].client.name)
    p0 = subprocess.Popen([executable, 'localhost'], 
                          cwd=gamedatas[0].client.name,
                          stdout=trash, stderr=trash)
    time.sleep(1)
    
    executable = '%s/%s/run' % (os.getcwd(), gamedatas[1].client.name)
    p1 = subprocess.Popen([executable, 'localhost', '1'], 
                          cwd=gamedatas[1].client.name,
                          stdout=trash, stderr=trash)
    
    # game is running. watch for gamelog
    game.status = "Running"
    game.save()
    while not os.access('server/logs/1.gamelog.bz2', os.F_OK):
        job.touch()
        time.sleep(1)

    [x.terminate() for x in [server, p0, p1]]
    trash.close()
    
    # FIXME determine winnner
        
    push_gamelog(game)
    game.status = "Complete"
    game.save()
    
    job.delete()
    stalk.close()
    
    
def push_gamelog(game):
    c = boto.connect_s3(access_cred, secret_cred)
    b = c.get_bucket('siggame-gamelogs')
    k = boto.s3.key.Key(b)
    k.key = "%s.gamelog.bz2" % game.pk
    k.set_contents_from_filename("server/logs/1.gamelog.bz2")
    k.set_acl('public-read')
    game.gamelog_url = 'http://siggame-gamelogs.s3.amazonaws.com/%s' % k.key
    game.save()
    os.remove("server/logs/1.gamelog.bz2")
    os.remove("server/logs/1.gamelog")


def get_fresh_server():
    git.Repo("/home/mnuck/megaminer8").remotes.origin.pull()
    shutil.rmtree('server', ignore_errors=True)
    shutil.copytree('/home/mnuck/megaminer8/server', 'server')
    
    
def update_local_repo(client):
    base_git_path = "ssh://mnuck@r99acm.device.mst.edu:2222/home/mnuck/clients/"
    try:
        git.Git().clone('%s%s.git' % (base_git_path, client))
    except git.exc.GitCommandError:
        pass
    git.Repo(client).remotes.origin.pull()

main()
