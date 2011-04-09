# -*- coding: iso-8859-1 -*-
class ShipAndDestination:
  def __init__(self,ship,port):
    self.ship = ship
    self.port = port
  
  @staticmethod
  def make(ship,port)

class MerchantAI:
  def __init__(self,game,id):
    self.game = game
    self.id = id
    self.numPirates = game.npcStartingPirates
    self.inTransit = []
    self.treasureThreshold = self.game.treasureThreshold
    self.halfPirate = 0
  
  def chooseRichestPort(self):
    richestPort = None
    richness = 0
    destiDensity = []
    index = 0
    for p in self.game.objects.values() if isinstance(p,Port) and (p.owner == 2 or p.owner == 3):
      destiDensity[index] = [0,p] 
      alreadyDestination = False
      for i in self.inTransit:
        if i.port is p:
          alreadyDestination = True
          destiDensity[index][0] += 1
      if not alreadyDestination:
        for t in self.game.objects.values() if isinstance(t,Treasure) and p.x == t.x and p.y == t.y:
          if t.amount > richness:
            richness = t.amount
            richestPort = p
      index += 1
    if richestPort == None:
      destiDensity.sort()
      richestPort = destiDensity[0][1]
    return richestPort
  
  def makeTradeShip(self,port):
    destination = self.chooseRichestPort(port)
    self.game.addObject(Ship.make(self.game,port.x,port.y,port.owner,self.game.shipHealth,self.game.shipStrength))
    for i in range(0,self.numPirates):
      self.game.addObject(Pirate.make(self.game,port.x,port.y,port.owner,self.game.pirateHealth,self.game.pirateStrength))
    treasureValue = 0
    for i in self.game.objects.values() if isinstance(i,Treasure) and i.x == port.x and i.y == port.y and i.pirateID == -1:
      treasureValue =  i.amount
    for i in self.game.objects.values() if isinstance(i,Pirate) and i.x == port.x and i.y == port.y and i.owner == port.owner:
      i.pickupTreasure(treasureValue/(2*self.numPirates))
    
  
  def pirateDied(self):
    self.numPirates += 1
    
  def pirateArrived(self,pirate):
    for i in self.game.objects.values() if isinstance(i,Treasure) and i.pirateID == pirate.id:
      pirate.dropTreasure(i.amount)
    self.game.removeObject(pirate)
    self.halfPirate += 1
    if self.halfPirate == 2:
      self.halfPirate = 0
      self.numPirates -= 1
      if self.numPirates == 0:
        self.numPirates = 1
  
  def shipArrived(self,ship):
    for i in self.game.objects.values() if (isinstance(i,Treasure) or isinstance(i,Pirate)):
      i.x = self.destinationPort.x
      i.y = self.destinationPort.y
    self.game.removeObject(ship)

  def play(self):
    