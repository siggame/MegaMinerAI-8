# -*- coding: utf-8 -*-
#New Game Visualizer Scheduler Update Function
#the game holders themselves are not deleted so that the queue can easily tell wether a game between these two with the same version numbers has already been played, as if one has it gets no bonus to its priority.

# each is of size n^2 - n where n is the number of teams.

# teamlist is a dict for current version numbers

import threading

class teamScore:
  def __init__(self,team,score):
    self.team = team
    self.score = score
    
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
  teamRank = []
  
  def __init__(self):
    self.tentq = []
    self.teamlist = {}
    self.teamRank = []
    
  #New Version Game Scheduler Update Function  
  def updateQueue(self, newAI, version):
    if newAI in self.teamlist:
      self.teamlist[newAI] = version
      for m in self.tentq:
        if newAI in [m.p1, m.p2]:
          m.priority =1
    else:
      for team in self.teamlist:
        self.tentq.append(Match(1, newAI, team))
        self.tentq.append(Match(1, team, newAI))
      self.teamlist[newAI] = version
      self.teamRank.append(teamScore(newAI,0))
    return True
    
  def removeCompetition(fight):
    try:
      self.tentq.remove(fight)
      return True
    except:
      return False

  #grabs the next game to be run by a tentacle and makes the proper adjustments
  def nextGame(self):
    self.tentq.sort(key = lambda x: x.priority, reverse=True)
    nextUp = self.tentq[0]    
    nextUp.priority -= 1
    return nextUp
  
  def ready(self):
    return len(self.tentq) > 0
    
  def done(self):
    #Never give up!
    return len(self.tentq) == 0
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
