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
    # loop through all of the bases
    for base in self.bases:
      # check if you own that base
      if base.getOwner() == self.playerID():
        # check to see if you have enough cycles to spawn a level 0 virus
        if self.baseCost() <= self.players[self.playerID()].getCycles():
          # spawn a level 0 virus at that base
          base.spawn(0)

    # loop through all of the viruses
    for virus in self.viruses:
      # if you own that virus
      if virus.getOwner() == self.playerID():
        # if the tile you want to move to is NOT a wall
        if self.getTileAtLocation(virus.getX()+1, virus.getY()).getOwner() != 3:
          # move the virus
          virus.move(virus.getX()+1, virus.getY())
    
    # End your turn
    return True;

  def __init__(self, conn):
      BaseAI.__init__(self, conn)
