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
     for base in self.bases:
      for player in self.players:
       if player.getId() == self.playerID():
        player.talk("IS THIS WORKING?")                
       if base.getOwner() == self.playerID() and base.getSpawnsLeft() > 0:
         base.spawn(0)
     for virus in self.viruses:
      for player in self.players:
       if player.getId() == self.playerID():
        player.talk("IMMA FIRIN MAH LAZAH BWARRHH!!!!")                     
       if virus.getOwner() == self.playerID() and virus.getMovesLeft > 0:
         if 2 > virus.getX():
           virus.move(virus.getX()+1,virus.getY())
         elif 2 < virus.getX():
           virus.move(virus.getX()-1,virus.getY())
         else:
           if 1 > virus.getY():
             virus.move(virus.getX(),virus.getY()+1)
           else:
             virus.move(virus.getX(),virus.getY()-1)     
     return 1

  def __init__(self, conn):
      BaseAI.__init__(self, conn)
