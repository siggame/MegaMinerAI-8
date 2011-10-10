import math
import random
import time
from tentacle import run_game
from celery.task.control import inspect

def run_games(games):
  results = [None]**len(games)
  queue = []
  done = False
  for g in games:
    queue.append(run_game.delay(g[0],g[1],str(g[0])+'.'+str(g[1])))
  while not done:
    for g in queue:
      if g.result != None:
        done = True
        break
  for g in range(len(queue)):
    results[g] = games[g][queue[g].result]

def _run_games(games):
  results = []
  for g in games:
    results.append(random.choice(g))
  return results

def swiss_round(players, rounds):
  results = dict()
  for p in players:
    results[p] = 0
  for r in range(rounds):
    print "round",r
    tiers = dict()
    for p in players:
      if results[p] not in tiers:
        tiers[results[p]] = [p]
      else:
        tiers[results[p]].append(p)
    games = []
    for t in tiers.itervalues():
      if len(t) % 2 == 1:
        t.append('shell')
      print t
      for i in range(0,len(t),2):
        games.append((t[i],t[i+1]))
    print games
    winners = run_games(games)
    for w in winners:
      if w != 'shell':
        results[w] += 1
  print results

    
      
def triple_elim(teams):
  #order matters, 0 > 1 > 2 ... approximately
  n = 3
  place = n
  players = teams[:]
  while math.log(len(players),2) < math.ceil(math.log(len(players),2)):
    players.append('shell')
  size = math.log(len(players),2)
  tiers = [players[:],[],[]]
  lastchance = []
  print tiers
  while len(players) > 1:
    newtiers = [[],[],[]]
    raw_input()
    for t in range(len(tiers)):
      if len(tiers[t]) == 1:
        newtiers[t].append(tiers[t][0])
        continue
      games = []
      for i in range(len(tiers[t])/2):
        games.append((tiers[t][i],tiers[t][-1-i]))
      print games
      results = run_games(games)
      for r in range(len(results)):
        winner = results[r]
        loser = games[r][0]
        if loser == winner:
          loser = games[r][1]
        if loser in lastchance:
          print loser,"finished",place
          place -= 1
          if place == 1:
            print winner,"wins"
            return
          players.remove(loser)
          newtiers[t-1].append(winner)
          continue
        newtiers[t].append(winner)
        if t < len(tiers)-1:
          newtiers[t+1].append(loser)
        else:
          players.remove(loser)
    notdone = False in [ len(l) <= 1 for l in tiers ]
    if not notdone:
      if len(lastchance) == 0:
        print "Final 3:",tiers[0][0],tiers[1][0],tiers[2][0]
      lasttier = len(tiers)-1
      while len(tiers[lasttier]) == 0:
        lasttier -= 1
      lastchance.append(tiers[lasttier][0])
      newtiers[lasttier-1].append(tiers[lasttier][0])
      newtiers[lasttier] = []
      print lastchance
    tiers = newtiers
    print tiers
  print players

clients = ['a','b','c','d','e','f','g','h','i']
triple_elim(clients)
