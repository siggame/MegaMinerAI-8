# -*- coding: iso-8859-1 -*-
from objects import *
import customastar
import random
class ShipAndDestination:
  def __init__(self,ship,port):
    self.ship = ship
    self.port = port
    self.pirates = []
    self.shitlist = []

class PortAndPirateNumber:
  def __init__(self,port,number):
    self.port = port
    self.number = number
    self.partial = 0

class MerchantAI:
  def __init__(self,game,id):
    self.game = game
    self.id = id
    self.numPirates = game.npcStartingPirates
    self.inTransit = []
    self.treasureThreshold = self.game.treasureThreshold
    self.thePorts = []
    for i in game.objects.values():
      if isinstance(i,Port):
        if i.owner == self.id:
          self.thePorts += [PortAndPirateNumber(i,self.numPirates)]
  
  #removes dying pirates and ships from shitlist
  def unlist(self,enemy):
    for group in self.inTransit:
      if enemy not in group.shitlist:
        continue
      else:
        group.shitlist.remove(enemy)
  
  def chooseRichestPort(self,port):
    richestPort = None
    richness = 0
    destiDensity = []
    index = 0
    for p in self.game.objects.values():
      if isinstance(p,Port) and (p.owner == 2 or p.owner == 3):
        if p is not port:
          destiDensity+= [[0,p]]
          alreadyDestination = False
          for i in self.inTransit:
            if i.port is p:
              alreadyDestination = True
              destiDensity[index][0] += 1
          if not alreadyDestination:
            for t in self.game.objects.values():
              if isinstance(t,Treasure) and p.x == t.x and p.y == t.y:
                if t.gold > richness:
                  richness = t.gold
                  richestPort = p
          index += 1
    if richestPort == None:
      destiDensity.sort()
      richestPort = destiDensity[0][1]
    return richestPort
  
  def makeTradeShip(self,portNum):
    port = self.thePorts[portNum].port
    destination = self.chooseRichestPort(port)
    newShip = Ship.make(self.game,port.x,port.y,port.owner,self.game.shipHealth,self.game.shipStrength)
    self.game.addObject(newShip)
    newInTransit = ShipAndDestination(newShip,destination)
    newShip.traderGroup = newInTransit
    treasureValue = 0
    for i in self.game.objects.values(): 
      if isinstance(i,Treasure) and i.x == port.x and i.y == port.y:
        treasureValue =  i.gold

    for i in range(0,self.thePorts[portNum].number):
      pirateDude = Pirate.make(self.game,port.x,port.y,port.owner,self.game.pirateHealth,self.game.pirateStrength)
      pirateDude.homeBase = portNum
      pirateDude.traderGroup = newInTransit
      pirateDude.pickupTreasure(treasureValue/(2*self.thePorts[portNum].number))
      self.game.addObject(pirateDude)
      newInTransit.pirates += [pirateDude]
    
    newShip.gold = int(treasureValue*(newShip._distance(destination.x,destination.y)/(self.game.mapSize*4.0)))
    self.inTransit += [newInTransit]
        
  
  def shipLost(self, ship):
    for i in self.inTransit:
      if i.ship is ship:
        self.inTransit.remove(i)
        
  def pirateDied(self,pirate):
    pirate.traderGroup.pirates.remove(pirate)
    self.thePorts[pirate.homeBase].number += 1
    
  def pirateArrived(self,pirate,homePort):
    pirate.dropTreasure(pirate.gold)
    self.game.removeObject(pirate)
    self.thePorts[homePort].partial += 1
    if self.thePorts[homePort].partial == 4:
      self.thePorts[homePort].partial = 0
      self.thePorts[homePort].number -= 1
      if self.thePorts[homePort].number == 0:
        self.thePorts[homePort].number = 1
  
  def shipArrived(self,ship,destinationPort):
    for i in self.game.objects.values():
      if isinstance(i,Pirate) and i.owner == self.id and i.x == ship.x and i.y == ship.y:
        self.pirateArrived(i,i.homeBase)
    self.game.removeObject(ship)
    
  def play(self):
    #removes empty ships
    for p in self.thePorts:
      for s in self.game.objects.values():
        if isinstance(s,Ship):
          if p.port.x == s.x and p.port.y == s.y and s.owner == -1:
            self.game.removeObject(s)
    for i in self.inTransit:
      deadEnemies = []
      for enemy in i.shitlist:
        if enemy not in self.game.objects.values():
          deadEnemies += [enemy]
      for enemy in deadEnemies:
        i.shitlist.remove(enemy)
          
      #if they didn't fight last turn, they can fight this turn
      enemyInRange = False
      for p in i.pirates:
        for j in i.shitlist:
          if isinstance(j,Pirate) and (j.owner == 0 or j.owner == 1) and j._distance(p.x,p.y) == 1:
            enemyInRange = True
            if p.attacksLeft > 0:
              p.attack(j)
              if self.game.objects.values().count(j) == 0:
                i.shitlist.remove(j)
                continue
            else:
              break
        if not enemyInRange:
          break
      if enemyInRange:
        for j in self.game.objects.values():
          if isinstance(j,Ship) and (j.owner == 0 or j.owner == 1) and j._distance(i.ship.x,i.ship.y) == 1:
            if i.ship.attacksLeft > 0:
              i.ship.attack(j)
              if self.game.objects.values().count(j) == 0:
                i.shitlist.remove(j)
                continue
            else:
              break
      if i.ship.attacksLeft <= 0:
        i.foughtLastTurn = True
        continue
      else:
        i.foughtLastTurn = False
      if abs(i.ship.x - i.port.x) + abs(i.ship.y -   i.port.y) == 0:
        self.shipArrived(i.ship,i.port)
        self.inTransit.remove(i)
      else:
        direction = customastar.aStar(self.game,1,i.ship.x,i.ship.y,i.port.x,i.port.y)
        #Right
        if len(direction) == 0:
          dir = random.randint(0,3)
          if dir == 0:
            direction = ['0']
          elif dir == 1:
            direction = ['1']
          elif dir == 2:
            direction = ['2']
          elif dir == 3:
            direction = ['3']
          #print "There is no path!"
        if direction[0] == '0':
          #print "right"
          i.ship.move(i.ship.x+1,i.ship.y)
        #Down
        elif direction[0] == '1': 
        #print "down"
          i.ship.move(i.ship.x,i.ship.y+1)
        #Left
        elif direction[0] == '2':
          #print "left"
          i.ship.move(i.ship.x-1,i.ship.y)
        #Up
        elif direction[0] == '3':
          #print "up"
          i.ship.move(i.ship.x,i.ship.y-1)
        #else:
          #print direction
          #print direction[0]
          #print `direction[0] == '0'`
    for p in self.thePorts:
      foundAShip = False
      isWorthy = False
      for i in self.game.objects.values():
        if isinstance(i,Treasure) and i.x == p.port.x and i.y == p.port.y and i.gold > self.treasureThreshold:
          isWorthy = True
        if isinstance(i,Ship) and i.x == p.port.x and i.y == p.port.y:
          foundAShip = True
      if isWorthy and not foundAShip:
        self.makeTradeShip(self.thePorts.index(p))