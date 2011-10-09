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
   print('This is my turn')
    #if self.turnNumber() <500:
   for base in self.bases:
       print('Spawnin stuff')
       base.spawn(random.randint(1,10))
   print self.turnNumber()
   for virus in self.viruses:
    if 0>1:
     dx = dy = 0
     print('move x','virus.x =',virus.getX())
     if virus.getX()<5:
       dx = 1
     elif virus.getX()>5:
       dx = -1
     elif virus.getX() is 5:
       print('move y')
       if virus.getY()>5:
        dy = -1
       elif virus.getY()<5:
         dy = 1
       elif virus.getY() is 5:
         dx = 1
     print('dx,dy',dx,dy)
     virus.move(virus.getX()+dx, virus.getY()+dy)
    elif 1 <= self.turnNumber() < 5:
      virus.move(virus.getX()+2,virus.getY()+2)
    elif 5 <= self.turnNumber() < 15:
      virus.move(virus.getX()-1,virus.getY())
    elif self.turnNumber() >= 15:
      virus.move(virus.getX(),virus.getY()+1)
    return 1

  def __init__(self, conn):
      BaseAI.__init__(self, conn)
