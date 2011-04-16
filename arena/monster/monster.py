#!/usr/bin/env python
# -*- coding: utf-8 -*-
from boto.ec2.connection import EC2Connection
from celery.task.control import inspect
from random import choice

import time

from tentacle import run_game

AWS_ACCESS_KEY = "AKIAICYAQREP6CMTOZ7Q" 
AWS_SECRET_KEY = "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"

ec2conn = EC2Connection(AWS_ACCESS_KEY, AWS_SECRET_KEY)

games = []

def startSpotTentacle():
  pass

players = [i.strip() for i in open('clients.txt') if i.strip()]
counter = 0

while True:
  inspector = inspect()
  numberwaiting = 0
  numberplaying = 0
  if inspector.scheduled() != None:
    numberwaiting = len(inspector.scheduled()) + len(inspector.reserved())
    numberplaying = len(inspector.active())
  if numberplaying > len(players)/2:
    print "would normally start another tentacle node"
  while numberwaiting < players*2:
    games.append(run_game.delay(choice(players),choice(players),str(counter)))
    counter += 1
  
  for g in games[:]:
    if g.result != None:
      print g.result
    games.remove(g)
  print len(games)
  time.sleep(2)
