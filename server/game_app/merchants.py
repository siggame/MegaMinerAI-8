# -*- coding: iso-8859-1 -*-
from objects import *
import customastar
class ShipAndDestination:
  def __init__(self,ship,port):
    self.ship = ship
    self.port = port

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
                if t.amount > richness:
                  richness = t.amount
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
    for i in range(0,self.thePorts[portNum].number):
      pirateDude = Pirate.make(self.game,port.x,port.y,port.owner,self.game.pirateHealth,self.game.pirateStrength)
      pirateDude.homeBase = portNum
      self.game.addObject(pirateDude)
    treasureValue = 0
    for i in self.game.objects.values(): 
      if isinstance(i,Treasure) and i.x == port.x and i.y == port.y and i.pirateID == -1:
        treasureValue =  i.amount
    for i in self.game.objects.values(): 
      if isinstance(i,Pirate) and i.x == port.x and i.y == port.y and i.owner == port.owner:
        i.pickupTreasure(treasureValue/(2*self.thePorts[portNum].number))
    self.inTransit += [ShipAndDestination(newShip,destination)]
  
  def pirateDied(self,homePort):
    self.thePorts[homePort].number += 1
    
  def pirateArrived(self,pirate,homePort):
    for i in self.game.objects.values():
      if isinstance(i,Treasure) and i.pirateID == pirate.id:
        pirate.dropTreasure(i.amount)
    self.game.removeObject(pirate)
    self.thePorts[homePort].partial += 1
    if self.thePorts[homePort].partial == 4:
      self.thePorts[homePort].partial = 0
      self.thePorts[homePort].number -= 1
      if self.thePorts[homePort].number == 0:
        self.thePorts[homePort].number = 1
  
  def shipArrived(self,ship,destinationPort):
    for i in self.game.objects.values():
      if isinstance(i,Treasure) and i.x == ship.x and i.y == ship.y:
        i.x = destinationPort.x
        i.y = destinationPort.y
    for i in self.game.objects.values():
      if isinstance(i,Pirate) and i.owner == self.id and i.x == ship.x and i.y == ship.y:
        i.x = destinationPort.x
        i.y = destinationPort.y
        if isinstance(i,Pirate):
          self.pirateArrived(i,i.homeBase)
    self.game.removeObject(ship)

  def play(self):
    for i in self.game.objects.values():
      if isinstance(i,Pirate) and i.id == self.id:
        for j in self.game.objects.values():
          if isinstance(j,Pirate) and j.id != 2 and j.id != 3:
            if i.hasAttacked == 0:
              i.attack(j)
    for i in self.game.objects.values():
      if isinstance(i,Ship) and i.id == self.id:
        for j in self.game.objects.values():
          if isinstance(j,Ship) and j.id != 2 and j.id != 3:
            if i.hasAttacked == 0:
              i.attack(j)
    for x in range(0,self.game.shipSteps):
      #Ships arrive at ports!
      for i in self.inTransit:
        if abs(i.ship.x - i.port.x) + abs(i.ship.y -   i.port.y) == 1:
          self.shipArrived(i.ship,i.port)
          self.inTransit.remove(i)
        else:
          direction = customastar.aStar(self.game,1,i.ship.x,i.ship.y,i.port.x,i.port.y)
          #Right
          if len(direction) == 0:
            continue 
            #print "There is no path!"
          elif direction[0] == '0':
            print "right"
            print i.ship.move(i.ship.x+1,i.ship.y)
          #Down
          elif direction[0] == '1':
            print "down"
            print i.ship.move(i.ship.x,i.ship.y+1)
          #Left
          elif direction[0] == '2':
            print "left"
            print i.ship.move(i.ship.x-1,i.ship.y)
          #Up
          elif direction[0] == '3':
            print "up"
            print i.ship.move(i.ship.x,i.ship.y-1)
          #else:
            #print direction
            #print direction[0]
            #print `direction[0] == '0'`
    for p in self.thePorts:
      foundAShip = False
      isWorthy = False
      for i in self.game.objects.values():
        if isinstance(i,Treasure) and i.x == p.port.x and i.y == p.port.y and i.pirateID == -1 and i.amount > self.treasureThreshold:
          isWorthy = True
        if isinstance(i,Ship) and i.x == p.port.x and i.y == p.port.y:
          foundAShip = True
      if isWorthy and not foundAShip:
        self.makeTradeShip(self.thePorts.index(p))