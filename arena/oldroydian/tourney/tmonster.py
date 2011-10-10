#!/usr/bin/env python
# -*- coding: utf-8 -*-
import rpyc

import tscheduler

import traceback

import config
import time

updateManagerName = 'localhost'


class ArenaMonster:
  tentacles = []

  
  def __init__(self):
    hosts = [i.strip() for i in open('serverList.txt') if i.strip()]

    self.tentacles = []
    for i in hosts:
        print i
        try:
          self.tentacles.append(rpyc.connect(i, 18861))
          self.tentacles[-1].host = i
        except:
          traceback.print_exc()
    print "Connected to",len(self.tentacles),"tentacles"
    
    self.scheduler = tscheduler.GameScheduler()
  
  def updateClients(self):
    validNames = config.readConfig('login.cfg')
    password = validNames['admin']['password']
    
    updateServer=rpyc.connect(updateManagerName,18862)
    versions = updateServer.root.getVersions(password)
    self.serverVersion = versions['server']
    
    for i in versions:
      if i in validNames and validNames[i]['player']:
        if i not in self.scheduler.teamlist or self.scheduler.teamlist[i] != versions[i]:
          self.scheduler.updateQueue(i, versions[i])
  
  def runMatch(self, tentacle, match):
    print 'My tentacle is fight.'
    print match
    tentacle.match = match
    if hasattr(tentacle, 'job'):
      if not tentacle.job.ready:
        return False
    p1 = match.p1
    p2 = match.p2
    f = rpyc.async(tentacle.root.runGame)
    tentacle.job = f((p1, self.scheduler.teamlist[p1]), (p2, self.scheduler.teamlist[p2]), self.serverVersion)
    return True
    
    
  def run(self):
    self.updateClients()
    while not self.scheduler.done():
      time.sleep(2)
      if not self.scheduler.ready():
        continue
      
      for i in self.tentacles:
        if not hasattr(i, 'job'):
          self.runMatch(i, self.scheduler.nextGame())
        elif i.job.ready:
          if job.value == 1:
            if(removeCompetition(i.match):
              for x in self.scheduler.teamRank:
                if x.team == i.match.p1:
                  x.score += 1 
          elif job.value == 2:
            if(removeCompetition(i.match):
              for x in self.scheduler.teamRank:
                if x.team == i.match.p2:
                  x.score += 1 
          
          #Do something with the result
          #So we don't have to treat tournament schedulers differently
          print i.job.value
          self.runMatch(i, self.scheduler.nextGame())
    for competitor in self.scheduler.teamRank:
      print "Team ",competitor.team,": ",competitor.score

if __name__ ==  '__main__':
    m = ArenaMonster()
    
    m.run()
