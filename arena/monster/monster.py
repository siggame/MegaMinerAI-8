#!/usr/bin/env python
# -*- coding: utf-8 -*-
from WebServerInterface import *
import time

from tentacle import run_game

AWS_ACCESS_KEY = "AKIAICYAQREP6CMTOZ7Q" 
AWS_SECRET_KEY = "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"

webserver = WebServerInterface("megaminerai.com")

games = []

def get_players():
  players = dict()
  logins = webserver.login_list()
  for l in logins:
    #print l
    players[l[0]] = l[1]
  return players

def update_versions(players):
  versions = {}
  for p in players:
    try:
      webs = webserver.get_ssh_path(players[p])
      if webs['commit_id'] == '':
        versions[p] = None
      else:
        versions[p] = webs['commit_id']
    except:
      versions[p] = None
  return versions


players = get_players()
versions = update_versions(players)

def priority_update(players, old_p, old_v, new_v):
  new_p = {}
  for p in players:
    if new_v[p] == None:
      continue
    update = False
    if old_v[p] == None:
      update = True
    if old_v[p] != new_v[p]:
      print "UPDATED:",players[p]
      update = True
    if update:
      for o in new_v:
        if new_v[o] == None or o == p:
          continue
        new_p[p,o] = old_p[max(old_p, key=lambda x: old_p[x])] + 1
    else:
      for o in new_v:
        if new_v[o] == None or o == p:
          continue
        new_p[p,o] = old_p[p,o]
  return new_p

def next_game(priorities):
  match = max(priorities, key=lambda x: priorities[x])
  priorities[match]=0
  for m in priorities:
    if m[0] in match or m[1] in match:
      continue
    priorities[m] += 1
  return match

priorities = {}
for p in versions:
  for o in versions:
    priorities[o,p] = 0

counter = 0

while True:
  #first update logins
  players = get_players()
  newVersions = update_versions(players)
  newPriorities = priority_update(players, priorities, versions, newVersions)
  versions = newVersions
  priorities = newPriorities
  print "TICK: max priority", priorities[max(priorities, key=lambda x: priorities[x])]
  #print priorities
  while len(games) < len(players)*2:
    nextg = next_game(priorities)
    print "adding game:",nextg
    games.append((run_game.delay(players[nextg[0]],players[nextg[1]],str(counter)),nextg))
    counter += 1
  for g in games[:]:
    if g[0].result != None:
      print g[0].result,g[1]
      games.remove(g)
  time.sleep(2)
