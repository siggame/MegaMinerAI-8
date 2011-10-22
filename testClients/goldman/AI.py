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
    for player in self.players:
      if player.getId() == self.playerID():
        player.talk("I am player: "+str(self.playerID()) + " on turn "+str(self.turnNumber()))
    for virus in self.viruses:
      if virus.getOwner() == self.playerID():
        virus.talk("I am virus: %i on turn %i at (%i,%i)"%(virus.getId(),self.turnNumber(), virus.getX(), virus.getY()))
        return 1
    
    for base in self.bases:
      if base.getOwner() == self.playerID():
        base.spawn(0)
    return 1

  def __init__(self, conn):
      BaseAI.__init__(self, conn)
