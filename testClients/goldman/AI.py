#-*-python-*-
from BaseAI import BaseAI
from GameObject import *
import BRAWLER
import random
from collections import deque

def distance(x1, y1, x2, y2):
    return abs(x1 - x2) + abs(y1 - y2)

class Move(object):
    def __init__(self, unit, x, y, fitness=0):
        self.unit = unit
        self.x = x
        self.y = y
        self.fitness = fitness
        self.lookup = {}

    def safeset(self, key, value):
        if key not in self.lookup:
            self.lookup[key] = value

    def __cmp__(self, other):
        return 1 if self.fitness > other.fitness else -1 if self.fitness < other.fitness else 0

    def execute(self):
        self.unit.move(self.x, self.y)

class Spawn(object):
    def __init__(self, level, fitness=0):
        self.level = level
        self.fitness = fitness

    def __cmp__(self, other):
        return 1 if self.fitness > other.fitness else -1 if self.fitness < other.fitness else 0


class AI(BaseAI):
  """The class implementing gameplay logic."""
  @staticmethod
  def username():
    return "BRAWLER"

  @staticmethod
  def password():
    return "ROBOTHOUSE"

  def init(self):
      self.opponent = 0 if self.playerID() == 1 else 1
      self.log = "%s.%i.brawl" % (self.players[self.opponent].getPlayerName(), self.playerID())
      self.pop, self.working = BRAWLER.getNext(self.log)
      self.offsets = [(0, 1), (1, 0), (0, -1), (-1, 0)]

      self.friendBases = set([(base.getX(), base.getY()) for base in self.bases if base.getOwner() == self.playerID()])
      self.enemyBases = set([(base.getX(), base.getY()) for base in self.bases if base.getOwner() == self.opponent])
      self.blocked = set([(base.getX(), base.getY()) for base in self.bases])

      self.valid = set([(tile.getX(), tile.getY()) for tile in self.tiles if tile.getOwner() != 3])
      for base in self.bases:
          self.valid.remove((base.getX(), base.getY()))



  def negdist(self, x1, y1, x2, y2):
      return (self.width() + self.height()) - distance(x1, y1, x2, y2)

  def mindist(self, x, y, options, conditional=lambda X: True):
      try:
          return max((self.negdist(x, y, op.getX(), op.getY()), op) for op in options if conditional(op))
      except ValueError:
          return (0, None)


  def end(self):
      self.working.fitness += (self.players[self.playerID()].getByteDollars() - self.players[self.opponent].getByteDollars())
      self.working.plays += 1
      BRAWLER.save(self.log, self.pop)

  def collectData(self, move, x, y, steps):
      key = (x, y)
      score = self.width() * self.height() - steps
      if key in self.openSpaces:
          move.safeset("openSpace", score)
      if key in self.enemySpaces:
          move.safeset("enemySpace", score)
      if key in self.enemyViruses:
          level, myLevel = self.enemyViruses[key].getLevel(), move.unit.getLevel()
          if level < myLevel:
              move.safeset("enemy<", score)
          elif level > myLevel:
              move.safeset("enemy>", score)
          else:
              move.safeset("enemy=", score)
      if key in self.friendViruses and self.friendViruses[key] is not move.unit:
          level, myLevel = self.friendViruses[key], move.unit.getLevel()
          if level == myLevel:
              move.safeset("friend=", score)
          else:
              move.safeset("friend!=", score)

  def searchOver(self, move):
      return (("openSpace" in move.lookup or len(self.openSpaces) == 0) and
              ("enemySpace" in move.lookup or len(self.enemySpaces) == 0) and
              ("enemy<" in move.lookup or "enemy=" in move.lookup or "enemy>" in move.lookup or len(self.enemyViruses) == 0) and
              ("friend=" in move.lookup or "friend!=" in move.lookup or len(self.friendViruses) < 2))

  def nearSearch(self, move):
      closed = set((move.x, move.y))
      open = deque([(move.x, move.y, 0)])
      count = 0

      while len(open) > 0 and not self.searchOver(move):
          working = open.pop()
          self.collectData(move, *working)
          for offset in self.offsets:
              x, y, steps = working[0] + offset[0], working[1] + offset[1], working[2] + 1
              if (x, y) in self.valid and (x, y) not in closed:
                  open.appendleft((x, y, steps))
                  closed.add((x, y))
      for key in BRAWLER.moveValues:
          move.safeset(key, 1)

  def run(self):
      moves = []
      self.openSpaces = set()
      self.enemySpaces = set()
      for tile in self.tiles:
          if (tile.getX(), tile.getY()) not in self.blocked:
              if tile.getOwner() == 2:
                  self.openSpaces.add((tile.getX(), tile.getY()))
              elif tile.getOwner() == self.opponent:
                  self.enemySpaces.add((tile.getX(), tile.getY()))

      self.enemyViruses = dict([((virus.getX(), virus.getY()), virus) for virus in self.viruses if virus.getOwner() == self.opponent and (virus.getX(), virus.getY()) not in self.enemyBases])
      self.friendViruses = dict([((virus.getX(), virus.getY()), virus) for virus in self.viruses if virus.getOwner() == self.playerID() and (virus.getX(), virus.getY()) not in self.friendBases])

      for virus in self.viruses:
          if virus.getOwner() == self.playerID():
              for offset in self.offsets:
                  x, y = virus.getX() + offset[0], virus.getY() + offset[1]
                  if (x, y) in self.valid:
                      moves.append(Move(virus, x, y))

      for base in self.bases:
          if base.getOwner() == self.playerID():
              base.spawn(0)
              '''
              "enemySpace",
              "combine",
              "enemyLevel",
              "myLevel"
              "friend",
              "enemy",
              "friendBase",
              "enemyBase",
              '''
      for move in moves:
          self.nearSearch(move)
          move.fitness = self.working.move.eval(move.lookup)
      random.shuffle(moves)
      moves.sort(reverse=True)
      for move in moves:
          if move.unit.getMovesLeft() > 0:
              print move.fitness
              move.execute()


      return 1

  def __init__(self, conn):
      BaseAI.__init__(self, conn)
