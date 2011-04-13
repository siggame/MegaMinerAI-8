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
      myUnits = [i for i in self.pirates if i.getOwner() == self.playerID()]
      myUnits[0].pickupTreasure(self.players[self.playerID()].getGold() - self.pirateCost())
      myPorts = [i for i in self.ports if i.getOwner() == self.playerID()]
      
      x = myUnits[0].getX()
      y = myUnits[0].getY()
      print x, y
      for i in self.tiles:
        if abs(i.getX() - myUnits[0].getX()) + abs(i.getY() - myUnits[0].getY()) == 1 and i.getType() == 0:
          x, y = i.getX(), i.getY()
          myUnits[0].move(i.getX(), i.getY())
          break
      print x, y
      for i in myUnits:
        i.attack(i)
      
      for i in self.ships:
        if i.getOwner() == self.playerID():
          i.attack(i)
      yield 1
      
      while self.turnNumber() < 400:
        print "Turn: ", self.turnNumber()
        print "Gold: ", max([i.getAmount() for i in self.treasures])
        yield 1
        
      print "Turn: ", self.turnNumber()
      print "I'm building a pirate!"
      
      myPorts[0].createPirate()
      
      yield 1
      print "Turn: ", self.turnNumber()
      print "I'm gettin' mah money!"
      
      myUnits = [i for i in self.pirates if i.getOwner() == self.playerID()]
      myUnits[0].move(x, y)
      
      amount = 0
      
      for i in self.treasures:
        if i.getX() == x and i.getY() == y:
          amount = i.getAmount()
          print "I'm picking up: ", amount
          myUnits[0].pickupTreasure(amount)
      
      yield 1
      
      print "Turn: ", self.turnNumber()
      print "I'm makin' a deposit!"
      myUnits[0].move(myPorts[0].getX(), myPorts[0].getY())
      myUnits[0].dropTreasure(amount)
      
      
      #gloat
      while True:
        print "Turn: ", self.turnNumber()
        print "Gold: ", self.players[self.playerID()].getGold()
        yield 1
      
      

  def __init__(self, conn):
      BaseAI.__init__(self, conn)
