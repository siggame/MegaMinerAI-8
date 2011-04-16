#-*-python-*-
from BaseAI import BaseAI

import random

class AI(BaseAI):
  """The class implementing gameplay logic."""
  @staticmethod
  def username():
    return "Shell AI"

  @staticmethod
  def password():
    return "password"

  def init(self):
    print "Initializing"

  def end(self):
    pass

  def run(self):
    print "Turn:", self.turnNumber
    print "My ID: ", self.playerID()
    print "My Gold: ", self.players[self.playerID()].gold()

    #if you have enough gold to buy a pirate
    if self.pirateCost < self.players[self.playerID()].gold():
      #find a port you own
      for p in self.ports:
        if p.getOwner == self.playerID():
          p.createPirate()
          break

    #for each pirate in the world
    for i in self.pirates:
      #if I own the pirate
      if i.getOwner == self.playerID():
        #select a random pirate from the list
        target = random.choice(pirates)
        #Does a naive path finding algoritm that only takes into account tyle types, not other blocking problems
        #Takes a start x, start y, end x, end y, and a tile type on which you wish to path
        path = self.getPath(i.getX(), i.getY(), target.getX(), target.getY(), 0)
        #for all but the last step of the path, while I have steps, move
        for step in path:
          if i.getMovesLeft() <= 0:
            break
          i.move(step.getX(), step.getY())
        #get the distance between the guys
        distance = abs(i.getX() - target.getX()) + abs(i.getY() - target.getY())
        #If the distance is exactly 1 away and I don't own the guy
        if distance == 1 and i.getOwner() != target.getOwner():
          while i.getAttacksLeft() > 0:
           #attack the target
           i.attack(target)

    return 1

  def __init__(self, conn):
      BaseAI.__init__(self, conn)
