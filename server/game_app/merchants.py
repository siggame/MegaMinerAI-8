# -*- coding: iso-8859-1 -*-
class MerchantAI:
  def __init__(self,game,id):
    self.game = game
    self.id = id
    self.numPirates = game.npcStartingPirates
    self.destinationPort = None
    
  def chooseRichestPort(self,merchant):
    richestPort = None
    richness = 0
    for p in self.game.objects.values() if isinstance(p,Port) and p.owner == merchant:
      for t in self.game.objects.values() if isinstance(t,Treasure) and p.x == t.x and p.y == t.y:
        if t.amount > richness:
          richness = t.amount
          richestPort = p
    return p
  
  def makeTradeShip(self,port):
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
      #Still working!
      