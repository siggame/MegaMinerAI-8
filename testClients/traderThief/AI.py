# -*- coding: iso-8859-1 -*-
#-*-python-*-
from BaseAI import BaseAI
from GameObject import *

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
      print "Units:" + `len(self.pirates)`
      myUnits = [i for i in self.pirates if i.getOwner() == self.playerID()]
      myShips = [i for i in self.ships if i.getOwner() == self.playerID()]
      myPorts = [i for i in self.ports if i.getOwner() == self.playerID()]
      if self.players[self.playerID()].getGold() > self.shipCost() and len(myShips) == 0:
        myPorts[0].createShip()
      for i in range(0,int( self.players[self.playerID()].getGold() / self.pirateCost())):
        myPorts[0].createPirate()
      print len(myUnits)
      for i in myUnits:
        for j in self.pirates:
          if j.getOwner() != self.playerID:
            if abs(j.getX()-i.getX())+abs(j.getY()-i.getY()) == 1:
              if i.getAttacksLeft() > 0:
                i.attack(j)
                break
        if i.getGold() > 0:
          i.dropTreasure(i.getGold())
      for i in myShips:
        for j in self.ships:
          if j.getOwner() != self.playerID:
            if abs(j.getX()-i.getX())+abs(j.getY()-i.getY()) == 1:
              if i.getAttacksLeft() > 0:
                i.attack(j)
                break
      return 1
      
      

  def __init__(self, conn):
      BaseAI.__init__(self, conn)
