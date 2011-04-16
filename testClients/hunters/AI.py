# -*- coding: iso-8859-1 -*-
#-*-python-*-
from BaseAI import BaseAI
from GameObject import *
from random import randint

def dist(x,y,destx,desty):
  return abs(x-destx)+abs(y-desty)

class battleGroup():
  def __init__(self,ship,pirates,netWorth):
    self.ship = ship
    self.pirates = pirates
    self.netWorth = netWorth

class AI(BaseAI):
  """The class implementing gameplay logic."""
  @staticmethod
  def username():
    return "Shell AI"

  @staticmethod
  def password():
    return "password"

  def init(self):
    pass

  def end(self):
    pass

  def run(self):
      myUnits = [i for i in self.pirates if i.getOwner() == self.playerID()]
      myShips = [i for i in self.ships if i.getOwner() == self.playerID()]
      myPorts = [i for i in self.ports if i.getOwner() == self.playerID()]
      
      #boards empty ships      #boards empty ships
      for p in myUnits:
        for e in self.ships:
          if e.getOwner() == -1:
            if dist(p.getX(),p.getY(),e.getX(),e.getY()) == 1:
              if len([i for i in myUnits if i.getX() == e.getX() and i.getY() == e.getY()]) == 0:
                p.move(e.getX(),e.getY())
      
      myBattleGroups = []
      for s in myShips:
        theMoneys = 0
        shipPirates = [i for i in myUnits if i.getX() == s.getX() and i.getY() == s.getY()]
        for p in shipPirates:
          theMoneys += p.getGold()
        theMoneys += s.getGold()
        myBattleGroups += [battleGroup(s,shipPirates,theMoneys)]
      
      #maketh new pirates
      for port in myPorts:
        piratesHere = [i for i in myUnits if i.getX() == port.getX() and i.getY() == port.getY()]
        for i in piratesHere:
          dumpEverything(i)
        if len([i for i in self.ships if i.getX() == port.getX() and i.getY() == port.getY()]) > 0:
          if len([i for i in myUnits if i.getX() == port.getX() and i.getY() == port.getY()]) < 12:
            for i in range(len([i for i in myUnits if i.getX() == port.getX() and i.getY() == port.getY()]),12):
              port.createPirate()
      
      for group in myBattleGroups:
        for p in group.pirates:
          self.attackAnything(p)
        best = None
        if group.netWorth > 0:
          best = myPorts[0]
          for port in myPorts:
            if dist(group.ship.getX(),group.ship.getY(),port.getX(),port.getY()) < dist(group.ship.getX(),group.ship.getY(),best.getX(),best.getY()):
              best = port
        else:
          targetShips = [i for i in self.ships if i.getOwner() == 2 or i.getOwner() == 3]
          best = group.ship
          if len(targetShips) > 0:
            best = targetShips[0]
          for target in targetShips:
            if dist(group.ship.getX(),group.ship.getY(),target.getX(),target.getY()) < dist(group.ship.getX(),group.ship.getY(),best.getX(),best.getY()):
              if len([i for i in self.pirates if i.getX() == target.getX() and i.getY() == target.getY()]) < len(group.pirates)/3:
                best = target
        print group.ship.getMovesLeft()
        direction = aStar(self,1,group.ship.getX(),group.ship.getY(),best.getX(),best.getY())
        if len(direction) == 0:
          dir = random.randint(0,3)
          if dir == 0:
            direction = ['0']
          elif dir == 1:
            direction = ['1']
          elif dir == 2:
            direction = ['2']
          elif dir == 3:
            direction = ['3']
        if len(direction) == 1:
          dir = random.randint(0,3)
          if dir == 0:
            direction += '0'
          elif dir == 1:
            direction += '1'
          elif dir == 2:
            direction += '2'
          elif dir == 3:
            direction += '3'
        #print "There is no path!"
        if direction[0] == '0':
          #print "right"
          group.ship.move(group.ship.getX()+1,group.ship.getY())
        #Down
        elif direction[0] == '1': 
        #print "down"
          group.ship.move(group.ship.getX(),group.ship.getY()+1)
        #Left
        elif direction[0] == '2':
          #print "left"
          group.ship.move(group.ship.getX()-1,group.ship.getY())
        #Up
        elif direction[0] == '3':
          #print "up"
          group.ship.move(group.ship.getX(),group.ship.getY()-1)
        print group.ship.getMovesLeft()
        if direction[1] == '0':
          #print "right"
          group.ship.move(group.ship.getX()+1,group.ship.getY())
        #Down
        elif direction[1] == '1': 
        #print "down"
          group.ship.move(group.ship.getX(),group.ship.getY()+1)
        #Left
        elif direction[1] == '2':
          #print "left"
          group.ship.move(group.ship.getX()-1,group.ship.getY())
        #Up
        elif direction[1] == '3':
          #print "up"
          group.ship.move(group.ship.getX(),group.ship.getY()-1)
        for p in group.pirates:
          self.attackAnything(p)
      return 1
      
  def attackAnything(self,pirate):
    for enemy in self.pirates:
      if enemy.getOwner() != self.playerID():
        if dist(pirate.getX(),pirate.getY(),enemy.getX(),enemy.getY()) == 1:
          if pirate.getAttacksLeft() > 0:
            pirate.attack(enemy)
          else:
            return

  def __init__(self, conn):
      BaseAI.__init__(self, conn)

def dumpEverything(pirate):
  if pirate.getGold() > 0:
    pirate.dropTreasure(pirate.getGold())
    
    
# A* Shortest Path Algorithm
# http://en.wikipedia.org/wiki/A*
# FB - 201012256
# modified by Jake Fischer
from heapq import heappush, heappop # for priority queue
import math
import time
import random

class node:
    xPos = 0 # x position
    yPos = 0 # y position
    distance = 0 # total distance already travelled to reach the node
    priority = 0 # priority = distance + remaining distance estimate
    def __init__(self, xPos, yPos, distance, priority):
        self.xPos = xPos
        self.yPos = yPos
        self.distance = distance
        self.priority = priority
    def __lt__(self, other): # comparison method for priority queue
        return self.priority < other.priority
    def updatePriority(self, xDest, yDest):
        self.priority = self.distance + self.estimate(xDest, yDest) * 10 # A*
    # give higher priority to going straight instead of diagonally
    def nextMove(self, dirs, d): # d: direction to move
        if dirs == 8 and d % 2 != 0:
            self.distance += 14
        else:
            self.distance += 10
    # Estimation function for the remaining distance to the goal.
    def estimate(self, xDest, yDest):
        xd = xDest - self.xPos
        yd = yDest - self.yPos
        # Euclidian Distance
        d = math.sqrt(xd * xd + yd * yd)
        # Manhattan distance
        # d = abs(xd) + abs(yd)
        # Chebyshev distance
        # d = max(abs(xd), abs(yd))
        return(d)

# A-star algorithm.
# The path returned will be a string of digits of directions.
def pathFind(the_map, n, m, dirs, dx, dy, xA, yA, xB, yB):
    closed_nodes_map = [] # map of closed (tried-out) nodes
    open_nodes_map = [] # map of open (not-yet-tried) nodes
    dir_map = [] # map of dirs
    row = [0] * n
    for i in range(m): # create 2d arrays
        closed_nodes_map.append(list(row))
        open_nodes_map.append(list(row))
        dir_map.append(list(row))

    pq = [[], []] # priority queues of open (not-yet-tried) nodes
    pqi = 0 # priority queue index
    # create the start node and push into list of open nodes
    n0 = node(xA, yA, 0, 0)
    n0.updatePriority(xB, yB)
    heappush(pq[pqi], n0)
    open_nodes_map[yA][xA] = n0.priority # mark it on the open nodes map

    # A* search
    while len(pq[pqi]) > 0:
        # get the current node w/ the highest priority
        # from the list of open nodes
        n1 = pq[pqi][0] # top node
        n0 = node(n1.xPos, n1.yPos, n1.distance, n1.priority)
        x = n0.xPos
        y = n0.yPos
        heappop(pq[pqi]) # remove the node from the open list
        open_nodes_map[y][x] = 0
        closed_nodes_map[y][x] = 1 # mark it on the closed nodes map

        # quit searching when the goal is reached
        # if n0.estimate(xB, yB) == 0:
        if x == xB and y == yB:
            # generate the path from finish to start
            # by following the dirs
            path = ''
            while not (x == xA and y == yA):
                j = dir_map[y][x]
                c = str((j + dirs / 2) % dirs)
                path = c + path
                x += dx[j]
                y += dy[j]
            return path

        # generate moves (child nodes) in all possible dirs
        for i in range(dirs):
            xdx = x + dx[i]
            ydy = y + dy[i]
            if not (xdx < 0 or xdx > n-1 or ydy < 0 or ydy > m - 1
                    or the_map[ydy][xdx] == 1 or closed_nodes_map[ydy][xdx] == 1):
                # generate a child node
                m0 = node(xdx, ydy, n0.distance, n0.priority)
                m0.nextMove(dirs, i)
                m0.updatePriority(xB, yB)
                # if it is not in the open list then add into that
                if open_nodes_map[ydy][xdx] == 0:
                    open_nodes_map[ydy][xdx] = m0.priority
                    heappush(pq[pqi], m0)
                    # mark its parent node direction
                    dir_map[ydy][xdx] = (i + dirs / 2) % dirs
                elif open_nodes_map[ydy][xdx] > m0.priority:
                    # update the priority
                    open_nodes_map[ydy][xdx] = m0.priority
                    # update the parent direction
                    dir_map[ydy][xdx] = (i + dirs / 2) % dirs
                    # replace the node
                    # by emptying one pq to the other one
                    # except the node to be replaced will be ignored
                    # and the new node will be pushed in instead
                    while not (pq[pqi][0].xPos == xdx and pq[pqi][0].yPos == ydy):
                        heappush(pq[1 - pqi], pq[pqi][0])
                        heappop(pq[pqi])
                    heappop(pq[pqi]) # remove the target node
                    # empty the larger size priority queue to the smaller one
                    if len(pq[pqi]) > len(pq[1 - pqi]):
                        pqi = 1 - pqi
                    while len(pq[pqi]) > 0:
                        heappush(pq[1-pqi], pq[pqi][0])
                        heappop(pq[pqi])       
                    pqi = 1 - pqi
                    heappush(pq[pqi], m0) # add the better node instead
    return '' # if no route found

def aStar(game, safeTile, startX, startY, endX, endY):
  #params:
  #  tiles is the list of tiles with x and y and type variables
  #  safeTile represents which tile we are path finding on, 0 = land, 1 = water
  #  startX is the X coordinate of the starting position
  #  startY is the Y coordinate of the starting position
  #  endX is the X coordinate of the end position
  #  endY is the Y coordinate of the end position
  #
  #returns:
  #  a route of integers, each integer represents a direction to move:
  #    0 = Right
  #    1 = Down
  #    2 = Left
  #    3 = Up
  
  #print "params: "
  #print "startX",
  #print startX
  #print "startY",
  #print startY
  #print "endX",
  #print endX
  #print "endY",
  #print endY
  
  
  #let's get all the tiles in the game!
  tiles = game.tiles
  
  ships = game.ships
  
  n = int(math.sqrt(len(tiles)))    # horizontal size of the map
  m = n     # vertical size of the map (right now we are assuming maps are sqaure
  
  #create empty map of 1's
  # NOTE: map[y][x] is how you acces it... odd
  the_map = []
  row = [1] * n  #1 is an invalid tile so we will fill the map with invalid tiles
  for i in range(m): # create empty map
    the_map.append(list(row))
  
  for tile in tiles:
    #if the tile we are looking at is the safe tile we need to make it safe, change it to a 0
    if tile.getType() == safeTile:
      the_map[tile.getY()][tile.getX()] = 0
  
  #mark all the ships as land tiles...
  for ship in ships:
    the_map[ship.getY()][ship.getX()] = 1   
  #also set the starting and ending positions to valid tiles!
  the_map[startY][startX] = 0;
  the_map[endY][endX] = 0;
 
  # these are valid directions that the pathfinder can move
  dirs = 4  # 4 driections (N, E, S, W)
  dx = [1, 0, -1, 0]
  dy = [0, 1, 0, -1]
  
  # this code is for 8 directions (N, NE, E, SE, S, SW, W, NW)
  # comment out the above if you want it and de comment this stuff below
  #dirs = 8
  #dx = [1, 1, 0, -1, -1, -1, 0, 1]
  #dy = [0, 1, 1, 1, 0, -1, -1, -1]
  
  #this finds the route through aStar!
  route = pathFind(the_map, n, m, dirs, dx, dy, startX, startY, endX, endY)
  
  #if len(route) == 0:
  #  print "returning an empty route"
  #else:
  #  print "returning a NON empty list"
  
  return route
    