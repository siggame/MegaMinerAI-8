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
      
      for i in self.tiles:
        if abs(i.getX() - myUnits[0].getX()) + abs(i.getY() - myUnits[0].getY()) == 1 and i.getType() == 0:
          myUnits[0].move(i.getX(), i.getY())
          break
      
      for i in myUnits:
        i.attack(i)
      
      for i in self.ships:
        if i.getOwner() == self.playerID():
          i.attack(i)
      yield 1
      
      while True:
        print "Turn: ", self.turnNumber()
        print max([i.getAmount() for i in self.treasures])
        yield 1

  def __init__(self, conn):
      BaseAI.__init__(self, conn)
