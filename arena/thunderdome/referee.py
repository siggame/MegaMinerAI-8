#!/usr/bin/env python
### Missouri S&T ACM SIG-Game Arena (Thunderdome)
#####

from datetime import datetime

import sys
if len(sys.argv) != 6:
    gladiator1   = 'localhost'
    gladiator2   = 'localhost'
    my_hostname  = 'mnuck.com'
    server_path  = '/home/mies/arena/server'
    print "referee.py gladiator1 gladiator2 my_hostname server_path"
else:
    (junk, gladiator, my_hostname, server_path) = sys.argv
    
# My AWS credentials
from aws_creds import access_cred, secret_cred, username, password

# Some magic to get a standalone python program hooked in to django
import sys
sys.path = ['/home/mies/', '/home/mies/mysite/mysite'] + sys.path

from django.core.management import setup_environ
import settings

setup_environ(settings)

# Non-Django 3rd Part Imports
import re, json               # special strings
import beanstalkc, git, boto  # networky
import subprocess, shutil, os # shellish
import random, time, os

# My Imports
from thunderdome.models import Game


from threading import Thread

class Smile_And_Nod(Thread):
    def __init__(self, pipe):
        Thread.__init__(self)
        self.pipe = pipe
        
    def run(self):
        while True:
            if len(self.pipe.readline()) == 0:
                break


def main():
    # FIXME eventually want a way to break out of this loop gracefully
    while True:
        looping()


def looping():
    # get a game
    stalk = beanstalkc.Connection()
    stalk.watch('game-requests')
    job = stalk.reserve(timeout=2)
    if job is None:
        stalk.close()
        return
    game_id = json.loads(job.body)['game_id']
    game = Game.objects.get(pk=game_id)
    print "processing game", game_id

    gamedatas = list(game.gamedata_set.all())
    random.shuffle(gamedatas) # even split of p0, p1        

    for x in gamedatas:
        update_local_repo(x.client)
    
    # handle embargoed players
    if any([x.client.embargoed for x in gamedatas]):
        game.status = "Failed"
        game.save()
        job.delete()
        stalk.close()
        print "failing the game, embargoed player"
        return
    
    # get and compile the clients
    gladiator = gladiator2
    for x in gamedatas:
        if gladiator == gladiator2:
            gladiator = gladiator1
        else:
            gladiator = gladiator2
        x.version = x.client.current_version
        update_downstream_repo(gladiator, x.client)
        result = remote_compile(gladiator, x.client)
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
        job.delete()
        stalk.close()
        print "failing the game, someone didn't compile"
        return
    
    players = list()
    
    e = ["ssh", "gladiator@%s" % gladiator1] + \
        ["cd %s ; ./run %s" % \
             (gamedatas[0].client.name, my_hostname)]
    players.append(subprocess.Popen(e, stdout=subprocess.PIPE,
                                    stderr=subprocess.PIPE))
    
    line = players[0].stdout.readline()
    match = re.search("Creating game (\d+)", line)
    if match:
        game_number = match.groups()[0]
    else:
        line = players[0].stderr.readline()
        if re.search("Unable to open socket", line):
            print "server is probably down. that's bad."
        else:
            print "unexpected output from client. bail."
        players[0].terminate()
        stalk.close()
        return

    # Player 0 is special, in that we need to read his output just
    # long enough to get the server game number. Once we have that
    # one datum, we ignore the rest of his output.
    nodder1 = Smile_And_Nod(players[0].stdout)
    nodder1.start()
    nodder2 = Smile_And_Nod(players[0].stderr)
    nodder2.start()
    
    e = ["ssh", "gladiator@%s" % gladiator2] + \
        ["cd %s ; ./run %s %s" % \
             (gamedatas[1].client.name, my_hostname, game_number)]
    players.append(subprocess.Popen(e, stdout=file("/dev/null", "w"),
                                    stderr=subprocess.STDOUT))

    # game is running. watch for compressed gamelog
    print "running..."
    game.status = "Running"
    game.save()
    print "%s/logs/%s.gamelog.bz2" % (server_path, game_number)
    while not os.access("%s/logs/%s.gamelog.bz2" % (server_path, game_number), 
                        os.F_OK):
        job.touch()
        time.sleep(1)
    
    time.sleep(1)
    # figure out who won by reading the gamelog
    print "determining winner..."
    winner = parse_gamelog(game_number)
    if winner == '0':
        gamedatas[0].won = True
        gamedatas[1].won = False
    elif winner == '1':
        gamedatas[0].won = False
        gamedatas[1].won = True
    [x.save() for x in gamedatas]        
        
    # clean up
    [x.join() for x in (nodder1, nodder2)]
    [x.terminate() for x in players]
    print "pushing gamelog..."
    push_gamelog(game, game_number)
    game.status = "Complete"
    game.completed = datetime.now()
    
    game.save()
    job.delete()
    stalk.close()    
    print "done!"


import socket
import libssh2
    
def remote_compile(hostname, client):
    command = 'cd %s ; make >/dev/null 2>/dev/null' % client.name
    return remote_call(hostname, command)


def update_downstream_repo(hostname, client):
    command = 'rm -rf %s' % client.name
    remote_call(hostname, command)
    command = 'git clone ssh://mies@%s%s/%s >/dev/null 2>/dev/null' % \
        (my_hostname, os.getcwd(), client.name)
    remote_call(hostname, command)
    

def remote_call(hostname, command):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((hostname, 22))

    session = libssh2.Session()
    session.startup(sock)

    session.userauth_password(username, password)
    channel = session.open_session()
    channel.execute(command)
    while not channel.eof():
        junk = channel.read(1024)
        time.sleep(1)
    
    result = channel.exit_status()
    session.close()
    return result        
    

def parse_gamelog(game_number):
    ### Determine winner by parsing that last s-expression in the gamelog
    f = open("%s/logs/%s.gamelog" % (server_path, game_number), 'r')
    log = f.readline()
    f.close()
    match = re.search("\"game-winner\" (\d) \"[\w ]+\" (\d+)", log)
    if match:
        return match.groups()[1]
    return None

    
def push_gamelog(game, game_number):
    ### Push the gamelog to S3
    c = boto.connect_s3(access_cred, secret_cred)
    b = c.get_bucket('siggame-gamelogs')
    k = boto.s3.key.Key(b)
    k.key = "%s.gamelog.bz2" % game.pk
    k.set_contents_from_filename("%s/logs/%s.gamelog.bz2" % \
                                     (server_path, game_number))
    k.set_acl('public-read')
    game.gamelog_url = 'http://siggame-gamelogs.s3.amazonaws.com/%s' % k.key
    game.save()
    os.remove("%s/logs/%s.gamelog.bz2" % (server_path, game_number))
    os.remove("%s/logs/%s.gamelog" % (server_path, game_number))
    
    
def update_local_repo(client):
    ### This is the repo the gladiators will be grabbing from
    base_path = "ssh://mnuck@r99acm.device.mst.edu:2222/home/mnuck/clients/"
    try:
        git.Git().clone('%s%s.git' % (base_path, client.name))
    except git.exc.GitCommandError:
        pass
    repo = git.Repo(client.name)
    stupid_string = 'thumbelalinaX'

    # clean up my mess from before
    repo.heads.master.checkout()
    my_head = [x for x in repo.heads if x.name == stupid_string]
    if( len(my_head) != 0 ):
        [repo.delete_head(x) for x in my_head]
        
    # get a fresh one
    repo.remotes.origin.pull()
    working_tags = [x for x in repo.tags if x.tag is not None]
    if( len(working_tags) != 0 ):
        newest = max(working_tags, key = lambda x: x.tag.tagged_date)
        # use the newest tag
        new_head = repo.create_head(stupid_string, commit=newest.commit)
        new_head.checkout()
        
        # maybe we can unembargo someone while we're at it
        if( newest.name != client.current_version ):
            client.current_version = newest.name
            client.embargoed = False
            client.save()
    
main()
