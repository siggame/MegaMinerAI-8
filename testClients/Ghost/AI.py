#-*-python-*-
from BaseAI import BaseAI
from GameObject import *
offsets = [(0,1), (1,0), (0,-1), (-1,0)]
diagonals = [(1,1), (1,-1),(-1,1),(-1,-1)]
import random
from collections import deque
def makeDict(mappable, test = lambda X: True):
  ret = {}
  for obj in mappable:
    if test(obj):
      ret[obj.getX(),obj.getY()] = obj
  return ret

def connect(openList, available):
  # Given a list of starting points and a set of valid points, find how many are connected to the start
  connected = set()
  while len(openList) > 0:
    working = openList.pop()
    connected.add(working)
    for offset in offsets:
      next = working[0] + offset[0], working[1] + offset[1]
      if next in available:
        available.remove(next)
        openList.append(next)
  return connected

class AI(BaseAI):
  """The class implementing gameplay logic."""
  @staticmethod
  def username():
    return "mst00120"

  @staticmethod
  def password():
    return "aegoaf5Y"

  def enemyTile(self, X): return X in self.valid and self.valid[X].getOwner() == self.enemyID
  def filterOffest(self, near, position): return filter(lambda X: self.enemyTile((X[0]+position[0], X[1]+position[1])), near)
  #'''
  def isCut(self, position):
    if not self.enemyTile(position): return False
    
    adj = self.filterOffest(offsets, position)+diagonals
    near = adj + self.filterOffest(diagonals, position)
    if len(adj) < 2: return False
    
    left = set(adj)
    while len(left) > 1:
      connect([left.pop()], near)
    return len(left) != 0
  '''
  
  def isCut(self, position):
    near = offsets+diagonals
    near = set(filter(lambda X: self.enemyTile((X[0]+position[0], X[1]+position[1])), near))
    brown = set([(1,1), (-1,-1)])
    yellow = set([(1, -1), (-1, 1)])
    green = set([(0, 1), (0, -1)])
    blue = set([(1, 0), (-1, 0)])
    return self.enemyTile(position) and ((bool(blue <= near) ^ bool(green<=near)) and not (bool(brown & near) and bool(yellow & near)))
  #'''  
      
      
  def biggestArea(self):
    p1, p2 = set(), set()
    # Builds a dictionary of all controlled tiles for both players
    for tile in self.tiles:
      if tile.getOwner() == 0:
        p1.add((tile.getX(), tile.getY()))
      elif tile.getOwner() == 1:
        p2.add((tile.getX(), tile.getY()))

    def maxArea(available):
      # Given a dictionary of valid tiles
      largest = 0
      ret = set()
      while len(available) > 0:
        next = available.pop()
        blob = connect([next], available)
        if largest < len(blob):
          largest = len(blob)
          ret = blob
      return ret
    p1blob, p2blob = maxArea(p1), maxArea(p2)
    # Convert the score to be a single point
    if self.playerID() == 0:
      return p1blob, p2blob
    else:
      return p2blob, p1blob

  def shortestNext(self, moves, virus, closest, test = lambda X: True, goal = lambda X: True):
    start = len(moves)
    searched = set(moves)
    openList = deque([])
    for move in moves:
      openList.append(move+(move, 0))
    count = 0
    goalDepth = 800
    goalFound = False
    while len(openList) > 0:
      count+=1
      x, y, move, depth = openList.pop()
      if count >= 200 or depth > goalDepth:
        break
      
      if goal((x, y)):
        if move is not None:
          if not goalFound:
            goalFound = True
            goalDepth = depth
            moves = []
          if move not in moves:
            moves.append(move)
      for offset in offsets:
        next = x+offset[0], y+offset[1]
        if test(next) and next not in searched:
          if closest and next in self.units and self.units[next].getLevel() >= virus.getLevel():
            openList.appendleft(next + (None,depth+1))
          else:
            openList.appendleft(next + (move,depth+1))
          searched.add(next)
    if len(moves) != start and len(moves) != 1:
      print "Multi:", start, len(moves)
    return moves


  def init(self):
    self.blocked = makeDict(self.bases)    
    self.valid = makeDict(self.tiles, lambda tile: (tile.getX(), tile.getY()) not in self.blocked and tile.getOwner()!=3)
    self.enemyID = 0 if self.playerID() == 1 else 1

  def end(self):
    pass
  
  def danger(self, virus, move):
    for offset in offsets:
      adj = move[0]+offset[0], move[1]+offset[1]
      if adj in self.units and self.units[adj].getOwner() != self.playerID() and self.units[adj].getLevel() > virus.getLevel():
        return True
    return False

  def run(self):
    print self.turnNumber(), [player.getByteDollars() for player in self.players]
    self.units = makeDict(self.viruses)
    self.myblob, self.enemyblob = self.biggestArea()
    self.myunconnected, self.enemyunconnected = set(), set()
    for at, tile in self.valid.iteritems():
      if tile.getOwner() == self.playerID() and at not in self.myblob:
        self.myunconnected.add(at)
      elif tile.getOwner() == self.enemyID and at not in self.enemyblob:
        self.enemyunconnected.add(at)

    # loop through all of the viruses
    for virus in self.viruses:
      # if you own that virus
      if virus.getOwner() == self.playerID() and virus.getMovesLeft() > 0:
        moves = [(virus.getX()+offset[0], virus.getY()+offset[1]) for offset in offsets] + [virus.getX(),virus.getY()]
        # only valid moves
        moves = filter(lambda move: move in self.valid, moves)
        # No running into other guys
        moves = filter(lambda move: move not in self.units or 
                      (self.units[move].getOwner() != self.playerID() and self.units[move].getLevel() <= virus.getLevel()) or
                      (self.units[move].getOwner() == self.playerID() and self.units[move].getLevel() == virus.getLevel()), moves)
                      
        moves = filter(lambda move: not self.danger(virus, move), moves)
        # From here down, moves become optional
        
        kills = filter(lambda move: move in self.units and self.units[move].getOwner() != self.playerID(), moves)
        if len(kills) > 0:
          moves = kills
      
        cut = filter(lambda move: self.isCut(move), moves)
        if len(cut) > 0:
          moves = cut
        
        enemySpace = filter(lambda move: self.valid[move].getOwner() == self.enemyID, moves)
        if len(enemySpace) > 0:
          moves = enemySpace
        bigblob = filter(lambda move: move in self.enemyblob, moves)
        if len(bigblob) > 0:
          moves = bigblob
        
        neutralSpace = filter(lambda move: self.valid[move].getOwner() == 2, moves)
        if len(neutralSpace) > 0:
          moves = neutralSpace
        
        if len(moves) > 1 and (virus.getX(), virus.getY()) not in self.myblob:
          moves = self.shortestNext(moves, virus, True, test = lambda X: X in self.valid, goal = lambda X: X in self.myblob)
        elif len(moves) > 1 and len(self.myunconnected) > 0:
          moves = self.shortestNext(moves, virus, True, test = lambda X: X in self.valid, goal = lambda X: X in self.myunconnected)
        # Part 6
        if len(moves) > 1:
          moves = self.shortestNext(moves, virus, True, test = lambda X: X in self.valid, 
                                    goal = lambda X: X in self.valid and (self.valid[X].getOwner() != self.playerID()))
        if len(moves) > 0:
          action = random.choice(moves)
          self.updateMove(virus, action)
    
    level = 0
    # loop through all of the bases
    for base in sorted(self.bases, key=lambda base: 
                       sum(abs(virus.getX()-base.getX())+abs(virus.getY()-base.getY()) for virus in self.viruses if virus.getOwner()==self.playerID()), reverse=True):
      # check if you own that base
      if base.getOwner() == self.playerID():
        # check to see if you have enough cycles to spawn a level 0 virus
        if self.baseCost()*self.scaleCost()**level <= self.players[self.playerID()].getCycles() and (base.getX(), base.getY()) not in self.units:
          # spawn a level 0 virus at that base
          base.spawn(level)

    # End your turn
    return True;
  
  def updateMove(self, virus, action):
    if action != (virus.getX(), virus.getY()):
      del self.units[virus.getX(), virus.getY()]
      virus.move(*action)
      if action not in self.units or self.units[action].getOwner() != self.playerID():
        self.units[action] = virus
    
  def __init__(self, conn):
      BaseAI.__init__(self, conn)
