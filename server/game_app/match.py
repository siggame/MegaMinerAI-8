# -*- coding: iso-8859-1 -*-
from base import *
from matchUtils import *
from objects import *
import networking.config.config
from collections import defaultdict
from networking.sexpr.sexpr import *
import os
import random
import itertools
import scribe

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
    self.player0Gold = 0
    self.player1Gold = 0
    self.player0Time = self.startTime
    self.player1Time = self.startTime
    self.boardX = self.mapX
    self.boardY = self.mapY
    
    cfgUnits = networking.config.config.readConfig("config/units.cfg")
    self.startMap(cfgUnits)
    self.startTreasures()
  
  def startMap(self, cfgUnits):
    map = [ [' ' for i in xrange(self.boardY)] for j in xrange(self.boardX)] 
    #open the map file for parsing
    f = open('maps/map1.txt', 'r')
    
    #these are basically booleans for when the map parser encounters special characters in the map files
    encounteredP = 0
    encountered1 = 0
    encountered2 = 0
    encountered3 = 0
    
    #before we parse the map we will get the attributes for the Pirates, and Ships from the units.cfg file
    PirateHealth = 1
    PirateStrength = 1
    PirateSteps = 1
    
    ShipsHealth = 1
    ShipsStength = 1
    ShipsSteps = 1
    
    #now we actually parse the units.cfg file
    for i in cfgUnits.keys():
      if "pirate" in i.lower():
        PirateHealth = cfgUnits[i]["health"]
        PirateStrength = cfgUnits[i]["strength"]
        PirateSteps = cfgUnits[i]["steps"]
      elif "ship" in i.lower():
        ShipHealth = cfgUnits[i]["health"]
        ShipStrength = cfgUnits[i]["strength"]
        ShipSteps = cfgUnits[i]["steps"]
    
    #this is where is parses through the map file and does tons of things!
    for y in range(0,self.boardY):
      for x in range(0,self.boardX):
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
              self.addObject(Pirate.make(self, x, y, 1, PirateHealth, PirateStrength))
              
            for i in range(0,self.playersStartingShips):
              self.addObject(Ship.make(self, x, y, 1, ShipHealth, ShipStrength))
              
          else:
            encounteredP = 0
            self.addObject(Port.make(self, x, y, 0))
            
            for i in range(0,self.playersStartingPirates):
              self.addObject(Pirate.make(self, x, y, 0, PirateHealth, PirateStrength))
              
            for i in range(0,self.playersStartingShips):
              self.addObject(Ship.make(self, x, y, 0, ShipHealth, ShipStrength))
              
        elif mapThing == '1':
        #if the next byte is a '1' which is a neutral AI's 1st port with land below it
          #map[x][y] = 0
          self.addObject(Tile.make(self, x, y, 0))
          if encountered1 == 1:
            self.addObject(Port.make(self, x, y, 3))
            
            for i in range(0,self.npcStartingPirates):
              self.addObject(Pirate.make(self, x, y, 3, PirateHealth, PirateStrength))
              
            for i in range(0,self.npcStartingShips):
              self.addObject(Ship.make(self, x, y, 3, ShipHealth, ShipStrength))
              
          else:
            self.addObject(Port.make(self, x, y, 2))
            
            for i in range(0,self.npcStartingPirates):
              self.addObject(Pirate.make(self, x, y, 2, PirateHealth, PirateStrength))
              
            for i in range(0,self.npcStartingShips):
              self.addObject(Ship.make(self, x, y, 2, ShipHealth, ShipStrength))
              
            encountered1 = 0
        elif mapThing == '2':
        #if the next byte is a '2' which is a neutral AI's 2nd port with land below it
          #map[x][y] = 0
          self.addObject(Tile.make(self, x, y, 0))
          if encountered2 == 1:
            self.addObject(Port.make(self, x, y, 3))
            
            for i in range(0,self.npcStartingPirates):
              self.addObject(Pirate.make(self, x, y, 3, PirateHealth, PirateStrength))
              
            for i in range(0,self.npcStartingShips):
              self.addObject(Ship.make(self, x, y, 3, ShipHealth, ShipStrength))
              
          else:
            self.addObject(Port.make(self, x, y, 2))
            
            for i in range(0,self.npcStartingPirates):
              self.addObject(Pirate.make(self, x, y, 2, PirateHealth, PirateStrength))
              
            for i in range(0,self.npcStartingShips):
              self.addObject(Ship.make(self, x, y, 2, ShipHealth, ShipStrength))
              
            self.addObject(Port.make(self, x, y, 2))
            encountered2 = 0
        elif mapThing == '3':
        #if the next byte is a '0' which is a neutral AI's 0th port with land below it
          #map[x][y] = 0
          self.addObject(Tile.make(self, x, y, 0))
          if encountered3 == 1:
            self.addObject(Port.make(self, x, y, 3))
            
            for i in range(0,self.npcStartingPirates):
              self.addObject(Pirate.make(self, x, y, 3, PirateHealth, PirateStrength))
              
            for i in range(0,self.npcStartingShips):
              self.addObject(Ship.make(self, x, y, 3, ShipHealth, ShipStrength))
              
          else:
            self.addObject(Port.make(self, x, y, 2))
            
            for i in range(0,self.npcStartingPirates):
              self.addObject(Pirate.make(self, x, y, 2, PirateHealth, PirateStrength))
              
            for i in range(0,self.npcStartingShips):
              self.addObject(Ship.make(self, x, y, 2, ShipHealth, ShipStrength))
              
            self.addObject(Port.make(self, x, y, 2))
            encountered3 = 0
      
    #for y in range(0,self.boardY):
      #print "\n",
      #for x in range(0,self.boardX):
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
    return object.move(x, y)

  @derefArgs(Unit, None)
  def talk(self, object, message):
    return object.talk(message, )

  @derefArgs(Pirate, None)
  def pickupTreasure(self, object, amount):
    return object.pickupTreasure(amount)

  @derefArgs(Pirate, None)
  def dropTreasure(self, object, amount):
    return object.dropTreasure(amount)

  @derefArgs(Pirate)
  def buildPort(self, object):
    return object.buildPort()

  @derefArgs(Pirate, Unit)
  def attack(self, object, Target):
    return object.attack(Target)

  @derefArgs(Port)
  def createPirate(self, object):
    return object.createPirate()

  @derefArgs(Port)
  def createShip(self, object):
    return object.createShip()

  @derefArgs(Ship, Unit)
  def attack(self, object, Target):
    return object.attack(Target)


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

    msg.append(["game", self.turnNumber, self.playerID, self.gameNumber, self.player0Time, self.player1Time])

    typeLists = []
    typeLists.append(["Pirate"] + [i.toList() for i in self.objects.values() if i.__class__ is Pirate])
    typeLists.append(["Port"] + [i.toList() for i in self.objects.values() if i.__class__ is Port])
    typeLists.append(["Ship"] + [i.toList() for i in self.objects.values() if i.__class__ is Ship])
    if self.turnNumber < 2:
      typeLists.append(["Tile"] + [i.toList() for i in self.objects.values() if i.__class__ is Tile])
    typeLists.append(["Treasure"] + [i.toList() for i in self.objects.values() if i.__class__ is Treasure])

    msg.extend(typeLists)

    return msg


loadClassDefaults()

