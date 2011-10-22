#-*-python-*-
from BaseAI import BaseAI
from GameObject import *
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
    pass

  def end(self):
    pass

  def run(self):
   toplevel = 0
   shark = False
   for rival in self.viruses:
    if rival.getOwner() == self.playerID(): 
     if rival.getLevel() > toplevel:
       toplevel = rival.getLevel()
   for base in self.bases:
    if shark == False:
      base.spawn(toplevel+2)
      shark = True
    else:
      base.spawn(0)
   for shark in self.viruses:
    if shark.getOwner() == self.playerID():
     if shark.getLevel() == toplevel+1:
       for rival in self.viruses:
        if rival.getOwner() != self.playerID(): 
         if rival.getLevel() == toplevel:
           if rival.getX() > shark.getX():
             shark.move(virusgetX()+1,shark.getY())
           elif rival.getX() < shark.level:
             shark.move(shark.getX()-1,shark.getY())
           else:
             if rival.getY() > shark.getY():
               shark.move(getX(),shark.getY()+1)
             else:
               shark.move(getX(),shark.getY()-1)
   for virus in self.viruses:
    if virus.getOwner() == self.playerID():
     virus.move(virus.getX()+1,virus.getY())
   return 1

  def __init__(self, conn):
      BaseAI.__init__(self, conn)
