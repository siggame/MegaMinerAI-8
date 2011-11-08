# -*- python -*-

from library import library

class BaseAI:
  """@brief A basic AI interface.

  This class implements most the code an AI would need to interface with the lower-level game code.
  AIs should extend this class to get a lot of builer-plate code out of the way
  The provided AI class does just that.
  """
  initialized = False
  iteration = 0
  runGenerator = None
  connection = None
  bases = []
  players = []
  tiles = []
  viruses = []

  def startTurn(self):
    from GameObject import Base
    from GameObject import Player
    from GameObject import Tile
    from GameObject import Virus

    BaseAI.bases = [Base(library.getBase(self.connection, i)) for i in xrange(library.getBaseCount(self.connection))]
    BaseAI.players = [Player(library.getPlayer(self.connection, i)) for i in xrange(library.getPlayerCount(self.connection))]
    BaseAI.tiles = [Tile(library.getTile(self.connection, i)) for i in xrange(library.getTileCount(self.connection))]
    BaseAI.viruses = [Virus(library.getVirus(self.connection, i)) for i in xrange(library.getVirusCount(self.connection))]

    if not self.initialized:
      self.initialized = True
      self.init()
    BaseAI.iteration += 1;
    if self.runGenerator:
      try:
        return self.runGenerator.next()
      except StopIteration:
        self.runGenerator = None
    r = self.run()
    if hasattr(r, '__iter__'):
      self.runGenerator = r
      return r.next()
    return r
  
  def turnNumber(self):
    return library.getTurnNumber(self.connection)

  def playerID(self):
    return library.getPlayerID(self.connection)

  def gameNumber(self):
    return library.getGameNumber(self.connection)

  def baseCost(self):
    return library.getBaseCost(self.connection)

  def scaleCost(self):
    return library.getScaleCost(self.connection)

  def width(self):
    return library.getWidth(self.connection)

  def height(self):
    return library.getHeight(self.connection)

  def getTileAtLocation(self, x, y):
    return self.tiles[x+y*self.width()]

  def __init__(self, connection):
    self.connection = connection
