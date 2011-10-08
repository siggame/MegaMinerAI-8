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
  #move a in multiple directions, was fun typing herp derp each time
#'''    herp_derp = self.turnNumber()%4
#    herp = derp = 0
#    if herp_derp is 0:
#      herp = 1
#      derp = 0
#    elif herp_derp is 1:
#      herp = -1
#      derp = 0
#    elif herp_derp is 2:
#      herp = 0
#      derp = 1
#    elif herp_derp is 3:
#      herp = 0
#      derp = -1'''
    print('This is my turn')
    if self.turnNumber() <3:
      for base in self.bases:
        base.spawn(random.randint(1,10))
    print self.turnNumber()
    for virus in self.viruses:
      dx = dy = 0
      if virus.getX()<5:
        dx = 1
      elif virus.getX()>5:
        dx = -1
      elif virus.getX() is 5:
        if virus.getY()>5:
         dy = -1
        elif virus.getY()<5:
          dy = 1
        elif virus.getY() is 5:
          dx = 1
      virus.move(virus.getX()+dx, virus.getY()+dy)
    return 1

  def __init__(self, conn):
      BaseAI.__init__(self, conn)
