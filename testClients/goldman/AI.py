#-*-python-*-
from BaseAI import BaseAI
from GameObject import *

class Move(object):
  def __init__(self, unit, x, y, score=0):
    self.unit = unit
    self.x = x
    self.y = y
    self.score = score

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
    
      return 1

  def __init__(self, conn):
      BaseAI.__init__(self, conn)
