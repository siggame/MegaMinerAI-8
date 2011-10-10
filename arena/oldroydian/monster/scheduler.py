# -*- coding: utf-8 -*-
#New Game Visualizer Scheduler Update Function
#the game holders themselves are not deleted so that the queue can easily tell wether a game between these two with the same version numbers has already been played, as if one has it gets no bonus to its priority.

# each is of size n^2 - n where n is the number of teams.

# teamlist is a dict for current version numbers

import threading

class Match:
  def __init__(self, priority, p1, p2):
    self.priority = priority
    self.p1 = p1
    self.p2 = p2
  
  def __repr__(self):
    return '%s VERSUS %s' % (self.p1, self.p2)

class GameScheduler:
  tentq = []
  teamlist = {}
  
  def __init__(self):
    self.tentq = []
    self.teamlist = {}
    
  #New Version Game Scheduler Update Function  
  def updateQueue(self, newAI, version):
    if newAI in self.teamlist:
      self.teamlist[newAI] = version
      for m in self.tentq:
        if newAI in [m.p1, m.p2]:
          m.priority += len(self.tentq)
          m.priority = min(m.priority, 2*len(self.tentq))
    else:
      for team in self.teamlist:
        self.tentq.append(Match(1, newAI, team))
        self.tentq.append(Match(1, team, newAI))
      self.teamlist[newAI] = version
    
    return True
      
  #Removes a competitor
  def removeCompetitor(self, removee):
    #Iterates through each of tentacle queue, visualizer queue, and team list.  Removes everything in which the team being removed participated.
    if removee in self.teamlist:
      del self.teamlist[removee]
    else:
      return False
    for s in self.tentq:
      if removee in [s.p1, s.p2]:
        self.tentq.remove(schedule)
    for game in visq:
      if removee in game:
        visq.remove(game)
    return True

  #grabs the next game to be run by a tentacle and makes the proper adjustments
  def nextGame(self):
    self.tentq.sort(key = lambda x: x.priority, reverse=True)
    nextUp = self.tentq[0]
    nextUp.priority = 0
    for s in self.tentq:
      if nextUp.p1 not in [s.p1, s.p2]:
        s.priority += 1
      if nextUp.p2 not in [s.p1, s.p2]:
        s.priority += 1
    
    return nextUp
  
  def ready(self):
    return len(self.tentq) > 0
    
  def done(self):
    #Never give up!
    return False
"""
#loop that checks for tentacles, gives them things to visualise, tentq contains priority, team1, team2, teams each contain teamName, version, AI.
def primaryScheduleLoop():
  tentq = {}
  visq = {}
  teamlist = {}
  while(running):
    #check for stop signal and stop if it says so
    #check for new AI
    #check for AI extraction requests
    #check for tentacles seeking work
    #check if the visualizer needs a log
  
  #once it finishes the loop, if it was told to run a tournament it runs a round robin tournament
  rrTournament(teamlist)


def rrTournament(teamlist):
  
"""
