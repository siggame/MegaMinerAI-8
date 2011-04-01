from base import *
from matchUtils import *
from objects import *
import networking.config.config
from collections import defaultdict
from networking.sexpr.sexpr import *
import os
import itertools
import scribe
import random

Scribe = scribe.Scribe

def loadClassDefaults(cfgFile = "config/defaults.cfg"):
  cfg = networking.config.config.readConfig(cfgFile)
  for className in cfg.keys():
    for attr in cfg[className]:
      setattr(eval(className), attr, cfg[className][attr])

class Match(DefaultGameWorld):
  def __init__(self, id, controller):
    
    self.id = int(id)
    self.controller = controller
    DefaultGameWorld.__init__(self)
    self.scribe = Scribe(self.logPath())
    self.addPlayer(self.scribe, "spectator")

    #TODO: INITIALIZE THESE!
    self.turnNumber = -1
    self.playerID = -1
    self.gameNumber = id
    
    self.pirateHealth = 1
    self.pirateStrength = 1
    self.pirateSteps = 1
    self.pirateCost = 1
    
    self.shipHealth = 1
    self.shipStrength = 1
    self.shipSteps = 1
    self.shipCost = 1
    self.shipRange = 1
    
    self.portCost = 1
    
    cfgUnits = networking.config.config.readConfig("config/units.cfg")
    self.startMap(cfgUnits)
    self.startTreasures()
    
  def startMap(self, cfgUnits):
    map = [ [' ' for i in xrange(self.mapSize)] for j in xrange(self.mapSize)] 
    
    #open the map file for parsing
    
    #first we will look for all the .map files in the maps/ folder
    mapFilenames = []
    #look through entire maps directory
    for filename in os.listdir("maps/"):
      #and if the filename ends in .map
      if ".map" in filename:
        mapFilenames.append(filename)
    
    #now we can open the map by randomly choosing a filename in that list
    f = open(("maps/" + mapFilenames[random.randint(0,len(mapFilenames) - 1)]), 'r')
    
    #these are basically booleans for when the map parser encounters special characters in the map files
    encounteredP = 0
    encountered1 = 0
    encountered2 = 0
    encountered3 = 0
    
    #before we parse the map we will get the attributes for the Pirates, and Ships from the units.cfg file

    
    #now we actually parse the units.cfg file
    for i in cfgUnits.keys():
      if "pirate" in i.lower():
        self.pirateHealth = cfgUnits[i]["health"]
        self.pirateStrength = cfgUnits[i]["strength"]
        self.pirateSteps = cfgUnits[i]["steps"]
        self.pirateCost = cfgUnits[i]["cost"]
      elif "ship" in i.lower():
        self.shipHealth = cfgUnits[i]["health"]
        self.shipStrength = cfgUnits[i]["strength"]
        self.shipSteps = cfgUnits[i]["steps"]
        self.shipCost = cfgUnits[i]["cost"]
        self.shipRange = cfgUnits[i]["range"]
      elif "port" in i.lower():
        self.portCost = cfgUnits[i]["cost"]
    
    #this is where is parses through the map file and does tons of things!
    for y in range(0,self.mapSize):
      for x in range(0,self.mapSize):
        mapThing = f.read(1)
        #mapThing = text[x][y]
        if mapThing == ' ':
        #if the next byte is a ' ', it is nothing so read the next character
          mapThing = f.read(1)
          
        if mapThing == '\r':
        #if the next byte is a '\r' (carrier return) it is nothing so read the next character
          mapThing = f.read(1)
          
        if mapThing == '\n':
        #if the next byte is a '\n' (newline) it is nothing so read the next character
          mapThing = f.read(1)
          
        if mapThing == '.':
        #if the next byte is a '.' which is water
          #map[x][y] = 1
          self.addObject(Tile.make(self, x, y, 1))
        elif mapThing == 'X':
        #if the next byte is a 'X' which is land
          #map[x][y] = 0
          self.addObject(Tile.make(self, x, y, 0))
        elif mapThing == 'P':
        #if the next byte is a 'P' which is land with a player's port on top
          #map[x][y] = 0
          self.addObject(Tile.make(self, x, y, 0))
          if encounteredP == 1:
            self.addObject(Port.make(self, x, y, 1))
            
            for i in range(0,self.playersStartingPirates):
              self.addObject(Pirate.make(self, x, y, 1, self.pirateHealth, self.pirateStrength))
              
            for i in range(0,self.playersStartingShips):
              self.addObject(Ship.make(self, x, y, 1, self.shipHealth, self.shipStrength))
              
          else:
            encounteredP = 1
            self.addObject(Port.make(self, x, y, 0))
            
            for i in range(0,self.playersStartingPirates):
              self.addObject(Pirate.make(self, x, y, 0, self.pirateHealth, self.pirateStrength))
              
            for i in range(0,self.playersStartingShips):
              self.addObject(Ship.make(self, x, y, 0, self.shipHealth, self.shipStrength))
              
        elif mapThing == '1':
        #if the next byte is a '1' which is a neutral AI's 1st port with land below it
          #map[x][y] = 0
          self.addObject(Tile.make(self, x, y, 0))
          if encountered1 == 1:
            self.addObject(Port.make(self, x, y, 3))
            
            for i in range(0,self.npcStartingPirates):
              self.addObject(Pirate.make(self, x, y, 3, self.pirateHealth, self.pirateStrength))
              
            for i in range(0,self.npcStartingShips):
              self.addObject(Ship.make(self, x, y, 3, self.shipHealth, self.shipStrength))
              
          else:
            self.addObject(Port.make(self, x, y, 2))
            
            for i in range(0,self.npcStartingPirates):
              self.addObject(Pirate.make(self, x, y, 2, self.pirateHealth, self.pirateStrength))
              
            for i in range(0,self.npcStartingShips):
              self.addObject(Ship.make(self, x, y, 2, self.shipHealth, self.shipStrength))
            encountered1 = 1
            
        elif mapThing == '2':
        #if the next byte is a '2' which is a neutral AI's 2nd port with land below it
          #map[x][y] = 0
          self.addObject(Tile.make(self, x, y, 0))
          if encountered2 == 1:
            self.addObject(Port.make(self, x, y, 3))
            
            for i in range(0,self.npcStartingPirates):
              self.addObject(Pirate.make(self, x, y, 3, self.pirateHealth, self.pirateStrength))
              
            for i in range(0,self.npcStartingShips):
              self.addObject(Ship.make(self, x, y, 3, self.shipHealth, self.shipStrength))
              
          else:
            self.addObject(Port.make(self, x, y, 2))
            
            for i in range(0,self.npcStartingPirates):
              self.addObject(Pirate.make(self, x, y, 2, self.pirateHealth, self.pirateStrength))
              
            for i in range(0,self.npcStartingShips):
              self.addObject(Ship.make(self, x, y, 2, self.shipHealth, self.shipStrength))
            
            encountered2 = 1
        elif mapThing == '3':
        #if the next byte is a '0' which is a neutral AI's 0th port with land below it
          #map[x][y] = 0
          self.addObject(Tile.make(self, x, y, 0))
          if encountered3 == 1:
            self.addObject(Port.make(self, x, y, 3))
            
            for i in range(0,self.npcStartingPirates):
              self.addObject(Pirate.make(self, x, y, 3, self.pirateHealth, self.pirateStrength))
              
            for i in range(0,self.npcStartingShips):
              self.addObject(Ship.make(self, x, y, 3, self.shipHealth, self.shipStrength))
              
          else:
            self.addObject(Port.make(self, x, y, 2))
            
            for i in range(0,self.npcStartingPirates):
              self.addObject(Pirate.make(self, x, y, 2, self.pirateHealth, self.pirateStrength))
              
            for i in range(0,self.npcStartingShips):
              self.addObject(Ship.make(self, x, y, 2, self.shipHealth, self.shipStrength))
            encountered3 = 1
      
    #for y in range(0,self.mapSize):
      #print "\n",
      #for x in range(0,self.mapSize):
        #print (map[x][y]),
        #self.addObject(Tile.make(self, x, y, map[x][y]))
    
  def startTreasures(self):
    #temp code that makes 2 treasures
    self.addObject(Treasure.make(self, 2, 8, -1, 100))
    self.addObject(Treasure.make(self, 8, 2, -1, 100))

  def addPlayer(self, connection, type="player"):
    connection.type = type
    if len(self.players) >= 2 and type == "player":
      return "Game is full"
    if type == "player":
      self.players.append(connection)
    elif type == "spectator":
      self.spectators.append(connection)
      #If the game has already started, send them the ident message
      if (self.turn is not None):
        self.sendIdent([connection])
    return True

  def removePlayer(self, connection):
    if connection in self.players:
      if self.turn is not None:
        winner = self.players[1 - self.getPlayerIndex(connection)]
        self.declareWinner(winner)
      self.players.remove(connection)
    else:
      self.spectators.remove(connection)

  def start(self):
    if len(self.players) < 2:
      return "Game is not full"
    if self.winner is not None or self.turn is not None:
      return "Game has already begun"
    
    #TODO: START STUFF

    self.turnNumber = -1
    #creates the players data
    for i in self.players:
      self.addObject(Player.make(self,i.screenName,self.playersStartingGold,self.startTime))
    #print self.objects.values()
    #print [i for i in self.objects.values() if isinstance(i,Player)]
    
    self.sendIdent(self.players + self.spectators)

    self.turn = self.players[1]

    self.nextTurn()
    return True


  def nextTurn(self):
    self.turnNumber += 1
    if self.turn == self.players[0]:
      self.turn = self.players[1]
      self.playerID = 1
    elif self.turn == self.players[1]:
      self.turn = self.players[0]
      self.playerID = 0

    else:
      return "Game is over."

    for obj in self.objects.values():
      obj.nextTurn()

    self.checkWinner()
    if self.winner is None:
      self.sendStatus([self.turn] +  self.spectators)
    else:
      self.sendStatus(self.spectators)
    self.animations = ["animations"]
    return True

  def checkWinner(self):
    #TODO: Make this check if a player won, and call declareWinner with a player if they did
    if self.turnNumber >= 500:
      self.declareWinner(self.players[0], 'Test Win for Player 0')
    #pass

  def declareWinner(self, winner, reason=''):
    self.winner = winner

    msg = ["game-winner", self.id, self.winner.user, self.getPlayerIndex(self.winner), reason]
    self.scribe.writeSExpr(msg)
    self.scribe.finalize()
    self.removePlayer(self.scribe)

    for p in self.players + self.spectators:
      p.writeSExpr(msg)

    self.sendStatus([self.turn])
    self.playerID ^= 1
    self.sendStatus([self.players[self.playerID]])
    self.playerID ^= 1
    self.turn = None
    
  def logPath(self):
    return "logs/" + str(self.id) + ".gamelog"

  @derefArgs(Unit, None, None)
  def move(self, object, x, y):
    return object.move(x, y, )

  @derefArgs(Unit, None)
  def talk(self, object, message):
    return object.talk(message, )

  @derefArgs(Unit, Unit)
  def attack(self, object, Target):
    return object.attack(Target, )

  @derefArgs(Pirate, None)
  def pickupTreasure(self, object, amount):
    return object.pickupTreasure(amount, )

  @derefArgs(Pirate, None)
  def dropTreasure(self, object, amount):
    return object.dropTreasure(amount, )

  @derefArgs(Pirate)
  def buildPort(self, object):
    return object.buildPort()

  @derefArgs(Port)
  def createPirate(self, object):
    return object.createPirate()

  @derefArgs(Port)
  def createShip(self, object):
    return object.createShip()


  def sendIdent(self, players):
    if len(self.players) < 2:
      return False
    list = []
    for i in itertools.chain(self.players, self.spectators):
      list += [[self.getPlayerIndex(i), i.user, i.screenName, i.type]]
    for i in players:
      i.writeSExpr(['ident', list, self.id, self.getPlayerIndex(i)])

  def getPlayerIndex(self, player):
    try:
      playerIndex = self.players.index(player)
    except ValueError:
      playerIndex = -1
    return playerIndex

  def sendStatus(self, players):
    for i in players:
      i.writeSExpr(self.status())
      i.writeSExpr(self.animations)
    return True


  def status(self):
    msg = ["status"]

    msg.append(["game", self.turnNumber, self.playerID, self.gameNumber, self.pirateCost, self.shipCost, self.portCost, self.mapSize])

    typeLists = []
    typeLists.append(["Pirate"] + [i.toList() for i in self.objects.values() if i.__class__ is Pirate])
    typeLists.append(["Player"] + [i.toList() for i in self.objects.values() if i.__class__ is Player])
    typeLists.append(["Port"] + [i.toList() for i in self.objects.values() if i.__class__ is Port])
    typeLists.append(["Ship"] + [i.toList() for i in self.objects.values() if i.__class__ is Ship])
    typeLists.append(["Tile"] + [i.toList() for i in self.objects.values() if i.__class__ is Tile])
    typeLists.append(["Treasure"] + [i.toList() for i in self.objects.values() if i.__class__ is Treasure])

    msg.extend(typeLists)

    return msg


loadClassDefaults()

