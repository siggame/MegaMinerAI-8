# -*- coding: iso-8859-1 -*-
#-*-python-*-
from BaseAI import BaseAI
from GameObject import *

import random

class mapTile:
  def __init__(self):
    self.gold = 0
    self.pirates = []
    self.port = None

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
    while True:
      print "Turn: ", self.turnNumber()
      myPirates = [i for i in self.pirates if i.getOwner() == self.playerID()]
      map = [ [ mapTile() for i in xrange(self.mapSize()) ] for j in xrange(self.mapSize()) ]
      for i in self.pirates:
        i.gold = i.getGold()
        map[i.getX()][i.getY()].pirates.append(i)
      
      for i in self.ports:
        map[i.getX()][i.getY()].port = i
      
      for i in self.treasures:
          map[i.getX()][i.getY()].gold += i.getGold()
      
      for i in map:
        for j in i:
          if j.pirates and j.pirates[0].getOwner() == self.playerID():
            if j.port:
              for k in j.pirates:
                if k.gold < 20:
                  k.pickupTreasure(20 - k.gold)
                else:
                  k.dropTreasure(k.gold - 20)
                k.gold = 20
            else:
              for k in j.pirates:
                k.dropTreasure(k.gold)
                j.gold += k.gold
                k.gold = 0
              num = len(j.pirates)
              for k in xrange(num):
                j.pirates[k].gold = (j.gold-1)/(num-k)
                j.pirates[k].pickupTreasure(j.pirates[k].gold)
                j.gold -= j.pirates[k].gold
                  
      
      for i in myPirates:
        x, y = random.choice( [(-1, 0), (1, 0), (0, -1), (0, 1)] )
        i.move(i.getX() + x, i.getY() + y)
      
      yield 1
      

  def __init__(self, conn):
      BaseAI.__init__(self, conn)
