#!/usr/bin/env python
# -*- coding: iso-8859-1 -*-
#from subprocess import Popen, PIPE, STDOUT
#import os, shutil
from os.path import isdir, exists, join
import traceback
#from bz2 import compress, decompress
import time
#from git import *
import sys

from boto.s3.connection import S3Connection
from boto.s3.key import Key
from celery.task import task
import pexpect

AWS_ACCESS_KEY = 'AKIAICYAQREP6CMTOZ7Q'

AWS_SECRET_KEY = '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'

GIT_PATH = "ssh://ubuntu@localhost/~/testClients/"#"ssh://david@r03dlokv6.device.mst.edu:2222/~/Dropbox/siggame/client-gits/"
password = ''

dbManagerName='r03mwwcp2.device.mst.edu'
s3conn = S3Connection(AWS_ACCESS_KEY, AWS_SECRET_KEY)
logbucket = s3conn.get_bucket("megaminer7")

port = "19000"

def update(program):
  print "updating",program
  if not exists(program):
    print 'cloning'
    command = "git clone " + GIT_PATH + program + '/.git'
    cwd = '.'
  else:
    print 'pulling'
    command = "git pull"
    cwd = program
  p = pexpect.spawn(command, cwd = cwd) 
  print "spawned a process:",command
  i = p.expect(['password:',pexpect.EOF])
  #if i == 0:
  #  p.sendline(password)
  #  p.expect(pexpect.EOF)
  #else:
  #  print "ERROR, can't clone git directory of",program
  #  return False
  print p.before

@task
def run_game(client1, client2, name):
  update(client1)
  update(client2)
  update('server')

  startTime = time.time()
  
  #now start the server...
  serverp = pexpect.spawn('python main.py '+port, cwd = 'server')
  #i = serverp.expect(['Starting Server',pexpect.EOF])
  #if i == 0:
  #  print "server started"
  #else:
  #  print "server failed to start"
    #return -1
  time.sleep(5)
  #now client 1...
  client1p = pexpect.spawn('/bin/bash ./run localhost:'+port, cwd = client1)
  i = serverp.expect(['Creating game 1',pexpect.EOF])
  if i == 0:
    print "game created!"
  else:
    print "game failed to create"
    return -2
  #and client 2...
  client2p = pexpect.spawn('/bin/bash ./run localhost:'+port+' 0', cwd = client2)
  i = client2p.expect(['',pexpect.EOF])
  if i == 0:
    print "game started!"
  else:
    print "game failed to start"
    return -3
  while time.time() < startTime + 600 and client1p.isalive() and client2p.isalive():
    time.sleep(5)
  print "game completed!"
  result = serverp.expect(["Tie game!","1 Wins!", "2 Wins", pexpect.TIMEOUT], timeout = 5)
  if result == 0:
    print client1, "wins"
  elif result == 1:
    print client2, "wins"
  elif result == 2:
    print "tie"
  elif result == 3:
    print "timeout!"
    return -4
  else:
    print "wat?"
    return -4
  serverp.close(True)
  client1p.close(True)
  client2p.close(True)

  logfile = open('server/logs/1.gamelog.bz2','rb')
  log = logfile.read()
  newkey = Key(logbucket)
  newkey.key = 'logs/'+name+str(time.time())+'.gamelog.bz2'
  newkey.set_contents_from_filename("server/logs/1.gamelog.bz2")
  
  return result

#run_game('move','gameover', 19000)
