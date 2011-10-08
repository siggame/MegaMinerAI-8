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
    print self.turnNumber()
    for base in self.bases:
      base.spawn(1)
    for virus in self.viruses:
      virus.move(virus.getX()+1, virus.getY())
    return 1

  def __init__(self, conn):
      BaseAI.__init__(self, conn)
