# -*- coding: iso-8859-1 -*-
#from merchants import *
from math import sqrt
class Mappable:
  def __init__(self, game, id, x, y):
    self.game = game
    self.id = id
    self.x = x
    self.y = y

  def toList(self):
    value = [
      self.id,
      self.x,
      self.y,
      ]
    return value

  def nextTurn(self):
    pass



class Unit(Mappable):
  def __init__(self, game, id, x, y, owner, health, strength, movesLeft, attacksLeft, gold):
    self.game = game
    self.id = id
    self.x = x
    self.y = y
    self.owner = owner
    self.health = health
    self.strength = strength
    self.movesLeft = movesLeft
    self.attacksLeft = attacksLeft
    self.gold = gold

  def toList(self):
    value = [
      self.id,
      self.x,
      self.y,
      self.owner,
      self.health,
      self.strength,
      self.movesLeft,
      self.attacksLeft,
      self.gold,
      ]
    return value

  def nextTurn(self):
    pass

  def move(self, x, y):
    print "Wrong move"
    return True

  def talk(self, message):
    self.game.animations.append(['talk', self.id, message])
    return true

  def attack(self, Target):
    pass
  
  def _distance(self, x, y):
    distance = abs(self.x-x)+abs(self.y-y)
    return distance

  def _takeDamage(self, damage):
    self.health -= damage
    if self.health < 1 and self.id in self.game.objects:
      self.game.removeObject(self)



class Pirate(Unit):
  def __init__(self, game, id, x, y, owner, health, strength, movesLeft, attacksLeft, gold):
    self.game = game
    self.id = id
    self.x = x
    self.y = y
    self.owner = owner
    self.health = health
    self.strength = strength
    self.movesLeft = movesLeft
    self.attacksLeft = attacksLeft
    self.gold = gold

  def toList(self):
    value = [
      self.id,
      self.x,
      self.y,
      self.owner,
      self.health,
      self.strength,
      self.movesLeft,
      self.attacksLeft,
      self.gold,
      ]
    return value

  @staticmethod
  def make(game, x, y, owner, health, strength):
    id = game.nextid
    game.nextid += 1
    # Placeholder for health and strength as 1, 1 respectively
    return Pirate(game, id, x, y, owner, health, strength, 0, 0, 0)

  def nextTurn(self):
    self.movesLeft = self.game.pirateMoves
    self.attacksLeft = self.game.pirateAttacks
    if self.game.playerID != self.owner:
      return True
    pass
    
  def takeDamage(self, pirate):
    self.health -= pirate.strength
    #If pirate is killed by the attack
    if self.health <= 0:
      #If the pirate did not kill himself, transfer gold to killing pirate... if it was a pirate that killed him
      if pirate.id != self.id and isinstance(pirate,Pirate):
        pirate.gold += self.gold
      #Otherwise the treasure becomes free game, or falls in your port, whichever
      
      else:
        if self.gold > 0:
          self.reallyDropTreasure(self.gold)
      if self.owner == 2:
        self.game.Merchant2.pirateDied(self.homeBase)
      if self.owner == 3:
        self.game.Merchant3.pirateDied(self.homeBase)
    
        #Lose control of ship if this is your last pirate leaving
      for i in self.game.objects.values():
        if isinstance(i,Ship) and i.x == self.x and i.y == self.y:
          if i.owner == self.owner:
            counter = 0
            #if the pirate was on a ship, count how many pirates are on it
            for j in self.game.objects.values():
              if isinstance(j,Pirate) and j.x == i.x and j.y == i.y:
                counter+=1
            #If this was the last pirate on board, the ship becomes neutral.
            if counter == 1:
              if i.owner == 2:
                self.game.Merchant2.shipLost(i)
              if i.owner == 3:
                self.game.Merchant3.shipLost(i)
              i.owner = -1
              
      self.game.removeObject(self)

    return True
          
      

  def move(self, x, y):
    #Checking to see if moving a valid piece
    if self.owner != self.game.playerID:
      return "Tried to move a unit that is not yours"  
 
    #Checks to see if the unit has moved this turn
    #0 if has not moved
    if self.movesLeft <= 0:
      return "This unit has already moved this turn"
    
    #Makes sure the unit is only moving one space
    if self._distance(x,y) > 1:
      return "Cannot move that far!"  
   
    elif self._distance(x,y) == 0:
      return "Already at that location"  

    #Checking to make sure the unit is in the bounds of the map
    if x > self.game.mapSize -1:
      return "Stepping off the world"
    elif y > self.game.mapSize -1:
      return "Stepping off the world"
    elif y < 0:
      return "Stepping off the world"
    elif x < 0:
      return "Stepping off the world"

    #Check to see if the unit is moving into an enemy
    for i in self.game.objects.values():
      if isinstance(i,Unit):
        if i.owner != -1 and i.owner != self.owner and i.x == x and i.y == y:
          return "Enemy at that location"
    for i in self.game.objects.values():
      #Check to see if the unit is moving into an enemy port
      if isinstance(i,Port):
        if i.owner != self.owner and i.x == x and i.y == y: 
          return "Moving into an enemy port"
      #Checking if unit is moving onto water
      elif isinstance(i,Tile) and i.x == x and i.y == y and i.type == 1:
        isShip = False
        for j in self.game.objects.values():
          if isinstance(j,Ship) and j.x == x and j.y == y:
            #-1 is placeholder value for neutral shop. May need to be changed
            if j.owner == self.owner or j.owner == -1:
              isShip = True

        if not isShip:
          return "Pirates cannot swim!"

    #Lose control of ship if this is your last pirate leaving
    for i in self.game.objects.values():
      if isinstance(i,Ship) and i.x == x and i.y == y:
        if i.owner == self.owner:
          counter = 0
          #if the pirate was on a ship, count how many pirates are on it
          for j in self.game.objects.values():
            if isinstance(j,Pirate) and j.x == i.x and j.y == i.y:
              counter+=1
          #If this was the last pirate on board, the ship becomes neutral.
          if counter == 1:
            i.owner = -1          
            
    #Moves the unit and makes it unable to move until next turn
    self.game.animations.append(['move', self.id,x,y])
    self.movesLeft -= 1
    self.x = x
    self.y = y
    
    #Take control of a ship if you are the first one on it
    for i in self.game.objects.values():
      if isinstance(i,Ship) and i.x == x and i.y == y:
        if i.owner == -1:
          i.owner = self.owner
    return True

  def talk(self, message):
    self.game.animations.append(['talk', self.id, message])
    return True

  def pickupTreasure(self, amount):
    if self.owner != self.game.playerID:
      return "Ye cannot make me pickup that therr treasurrr. Ye be not my captain!"  
    #If trying to use pickup treasure and standing on a port  
    portPickup = False
    for i in self.game.objects.values():       
      if isinstance(i,Port):
        if i.x == self.x and i.y == self.y and (i.owner == 0 or i.owner == 1):
          portPickup = True
    if amount < 1:
      return "Your must pickup more than nothing"
    if portPickup == True:
      p = [i for i in self.game.objects.values() if isinstance(i,Player)]
      #Sets the owner of the pirate to eaither player 0 or 1
      if self.owner == 0:
        owner = 0
      else:
        owner = 1
      #Checks to make sure amount being withdrawn is less than that player has
      if amount <= p[owner].gold:
        self.gold += amount
        p[owner].gold -= amount
        return True
      else:
        return "You do not have that much gold!"
              
    #If the pirate is not on a port and is trying to pickup Treasure
    if portPickup == False:
      treasurePickup = False
      for i in self.game.objects.values():
        if isinstance(i,Treasure):
          if i.x == self.x and i.y == self.y:
            #Check to make sure the amount being picked up isn't greater than its value
            if amount > i.gold:
              return "There isn't that much treasure!"
            #Checks to see if the pirate has treasure
            if amount == i.gold:
              self.gold += amount
              self.game.removeObject(i)
            elif amount < i.gold:
              i.gold -= amount
              self.gold += amount
            treasurePickup = True
            return True
      if treasurePickup == False:
        for i in self.game.objects.values():
          if isinstance(i,Ship):
            i.gold -= amount
            self.gold += amount
            return True
    
    return True
  
  def dropTreasure(self, amount):
    if self.owner != self.game.playerID:
      return "Yarr!  Ye cannot trick me into dropin me treasure!  Yer not me captain!" 
    return self.reallyDropTreasure(amount)
  
  #added this so I can call the drop treasure function without it checking wether or not it is that unit's turn, should make the killing of oneself easier.
  def reallyDropTreasure(self,amount):
    if amount > self.gold:
      return "Not that much gold to drop"
    if amount < 1:
      return "You need to drop gold!"
    for j in self.game.objects.values():
      #if the treasure is being dropped on a port
      if isinstance(j,Port) and (j.owner == 0 or j.owner == 1):
        if self.x == j.x and self.y == j.y:
          #Increase gold of owner
          if self.owner == 0:
            p = [k for k in self.game.objects.values() if isinstance(k,Player)]
            p[0].gold += amount
          else:
            p = [k for k in self.game.objects.values() if isinstance(k,Player)]
            p[1].gold += amount
          #Decrement gold if only partially dropped
          self.gold -= amount
          return True
    for j in self.game.objects.values():    
      if isinstance(j,Treasure):
        if self.x == j.x and self.y == j.y:
          j.gold += amount
          self.gold -= amount
          return True
    for j in self.game.objects.values():
      if isinstance(j,Ship):
        if self.x == j.x and self.y == j.y:
          j.gold += amount
          self.gold -= amount
          return True
    self.addObject(Treasure.make(self.game,self.x,self.y,amount))
    self.gold -= amount
    return True
                      
  def buildPort(self):
    if self.owner != self.game.playerID:
      return "Yarr, ye can't make me build a port! Ye are not my captain!"  
    #checks for distance to nearest port
    for i in self.game.objects.values():
      if isinstance(i,Port):
        if self._distance(i.x,i.y) <= 3:
          return "Too close to another port!"
    for i in self.game.objects.values():
      if isinstance(i, Tile):
        if i._distance(self.x,self.y) == 1: #Not sure about this
          if i.type == 1:
            if self.owner == 0:
              p = [i for i in self.game.objects.values() if isinstance(i,Player)]
              if p[0].gold >= self.game.portCost:
                #Checks to see if there is treasure on the loaction of the new port
                for j in self.game.objects.values():
                  if isinstance(j,Treasure) and j.x == self.x and j.y == self.y:
                    p[0].gold += j.gold
                    self.game.removeObject(j)
                p[0].gold -= self.game.portCost
                port = i.make(self.game,self.x,self.y,self.owner)
                self.game.addObject(port)
                return True
              else:
                return "Not enough gold to make this purchase"
            else:
              p = [i for i in self.game.objects.values() if isinstance(i,Player)]
              if p[1].gold >= self.game.portCost:
                #Checks to see if there is treasure on the loaction of the new port
                for j in self.game.objects.values():
                  if isinstance(j,Treasure) and j.x == self.x and j.y == self.y:
                    p[1].gold += j.gold
                    self.game.removeObject(j)
                p[1].gold -= self.game.portCost
                port = i.make(self.game,self.x,self.y,self.owner)
                self.game.addObject(port)
                return True
              else:
                return "Not enough gold to make this purchase"
          else:
           return "No water connected to this location"
            
    return True
  #TODO: Test and review this logic

  def attack(self, Target):
    #Ensures that you own the attacking unit
    if self.owner != self.game.playerID:
      return "I do not take orders from you! You be not my captain"
      
    elif not isinstance(Target,Unit):
      return "That isn't attackable!"
    
    elif self.attacksLeft <= 0:
      return "You've already attacked!"
    
    elif not (abs(self.x - Target.x)+abs(self.y  - Target.y) <= 1):
      return "That is too far away!"
    
    else:
      self.attacksLeft -= 1
      #Optional Ally Pirate Auto Kill
      if isinstance(Target,Pirate) and Target.owner is self.owner:
        Target.health = 0
      self.game.animations.append(['PirateAttack', self.id,Target.x,Target.y])
      Target.takeDamage(self)
      return True




class Player:
  def __init__(self, game, id, playerName, gold, time):
    self.game = game
    self.id = id
    self.playerName = playerName
    self.gold = gold
    self.time = time

  def toList(self):
    value = [
      self.id,
      self.playerName,
      self.gold,
      self.time,
      ]
    return value

  def nextTurn(self):
    pass
  
  @staticmethod
  def make(game, playerName, gold, time):
    id = game.nextid
    game.nextid += 1
    return Player(game, id, playerName, gold, time)

class Port(Mappable):
  def __init__(self, game, id, x, y, owner):
    self.game = game
    self.id = id
    self.x = x
    self.y = y
    self.owner = owner

  def toList(self):
    value = [
      self.id,
      self.x,
      self.y,
      self.owner,
      ]
    return value

  @staticmethod
  def make(game, x, y, owner):
    id = game.nextid
    game.nextid += 1
    return Port(game, id, x, y, owner)
    
  def nextTurn(self):
    pass
    

  def createPirate(self):
    if self.owner != self.game.playerID:
      return "That isn't your port!"
    #Decrememnting gold of corresponding player
    if self.owner == 0:
      p = [i for i in self.game.objects.values() if isinstance(i,Player)]
      if p[0].gold >= self.game.pirateCost:
        p[0].gold -= self.game.pirateCost
      else:
        return "Not enough gold for that unit"
    else:
      p = [i for i in self.game.objects.values() if isinstance(i,Player)]
      if p[1].gold >= self.game.pirateCost:
        p[1].gold -= self.game.pirateCost
      else:
        return "Not enough gold for that unit"
    pirate = Pirate.make(self.game, self.x, self.y, self.owner, self.game.pirateHealth, self.game.pirateStrength) #placeholder values
    self.game.addObject(pirate)
    return True
  #TODO: Test and review this logic

  def createShip(self):
    if self.owner != self.game.playerID:
      return "That isn't your port!"
    #Decrememnting gold of corresponding player
    if self.owner == 0:
      p = [i for i in self.game.objects.values() if isinstance(i,Player)]
      if p[0].gold >= self.game.shipCost:
        p[0].gold -= self.game.shipCost
      else:
        return "Not enough gold for that unit"
    else:
      p = [i for i in self.game.objects.values() if isinstance(i,Player)]
      if p[1].gold >= self.game.shipCost:
        p[1].gold -= self.game.shipCost
      else:
        return "Not enough gold for that unit"
    #Checks to make sure there is no other ships in the port
    for i in self.game.objects.values():
      if isinstance(i,Ship) and i.x == self.x and i.y == self.y:
        return "There is already a ship in the port"      
    ship = Ship.make(self.game, self.x, self.y, self.owner, self.game.shipHealth, self.game.shipStrength) #placeholder values
    self.game.addObject(ship)
    return True    
    pass



class Ship(Unit):
  def __init__(self, game, id, x, y, owner, health, strength, movesLeft, attacksLeft, gold):
    self.game = game
    self.id = id
    self.x = x
    self.y = y
    self.owner = owner
    self.health = health
    self.strength = strength
    self.movesLeft = movesLeft
    self.attacksLeft = attacksLeft
    self.gold = gold

  def toList(self):
    value = [
      self.id,
      self.x,
      self.y,
      self.owner,
      self.health,
      self.strength,
      self.movesLeft,
      self.attacksLeft,
      self.gold,
      ]
    return value

  @staticmethod
  def make(game, x, y, owner, health, strength):
    id = game.nextid
    game.nextid += 1
    # Placeholder for health and strength as 1, 1 respectively
    return Ship(game, id, x, y, owner, health, strength, 0, 0, 0)

  def nextTurn(self):
    self.movesLeft = self.game.shipMoves
    self.attacksLeft = self.game.shipAttacks

  def move(self, x, y):
    #Check the owner of the ship before moving
    if self.owner != self.game.playerID:
      return "This be not yarr ship, ye swine!"
      
    if self.movesLeft <= 0:
      return "This ship has already expended all of its moves this turn" 
     
    if self._distance(x,y) > 1:
      return "Cannot move that far!"
   
    elif self._distance(x,y) == 0:
      return "Already at that location"
    
    #Checking the bounds of the map
    if x > self.game.mapSize -1:
      return "Stepping off the world"
    elif y > self.game.mapSize -1:
      return "Stepping off the world"
    elif y < 0:
      return "Stepping off the world"
    elif x < 0:
      return "Stepping off the world" 
     
    #Makes sure the ship stays on water
    for i in self.game.objects.values():
      if isinstance(i,Tile) and i.x == x and i.y == y:
        #If the ship is attempting to move onto a land tile
        if i.type != 1:
          #This variable checks whether or not the ship is trying to move onto a port
          portTile = False
          for j in self.game.objects.values():
            if isinstance(j,Port):
              if j.x == x and j.y == y:
                #True if we find a port at desired location
                portTile = True
                #If the port does not belong to you, throw an error
                if j.owner != self.game.playerID:
                  return "You cannot move into enemy ports!"
          #If the player is simply trying to move a ship onto land
          if portTile == False:
            return "Ships cannot walk!"
      
    #Makes sure there is no units at target location
    for i in self.game.objects.values():
      if isinstance(i,Ship):
        if i.x == x and i.y == y:
          return "There is already a ship at that location" 

    #Ship has passed all checks and it ready to move
    self.movesLeft -= 1
    
    #Moving all treasure,pirates on the ship to the new location
    #Also moves the ship to the new location
    for i in self.game.objects.values():
      if isinstance(i,Pirate) and i.x == self.x and i.y == self.y:
        i.x = x
        i.y = y
    self.x = x
    self.y = y
    #auto dumps treasure if arriving at a port
    for i in self.game.objects.values():
      if isinstance(i,Port) and i.x == x and i.y == y:
        p = [i for i in self.game.objects.values() if isinstance(i,Player)]
        p[self.owner].gold += self.gold
        self.gold = 0
        
    return True
    
  def talk(self, message):
    pass

  def attack(self, Target):
    #Make sure you own the attacking unit
    if self.owner != self.game.playerID:
      return "This be not yarr ship, ye swine!"
     
    #Checks to see that the target is in range     
    if self._distance(Target.x,Target.y) > self.game.shipRange:
      return "That target is not in your range"      
      
    #Makes sure the opponent's type is ship
    if isinstance(Target,Ship) == False:
      return "You may only attack ships with your ship"
      
    #Meets all conditions for attack
    if self.attacksLeft <= 0:
      return "You may only attack once with a ship each turn"
    self.attacksLeft -= 1   
    self.game.animations.append(['ShipAttack', self.id,Target.x,Target.y])
    Target.takeDamage(self)
    return True
    
  def takeDamage(self, attacker):
    self.health -= attacker.strength
    #If the ship is killed by the attack
    #Destroy everything that was on it
    #If it was not at a port
    if self.health <= 0:
      atPort = False
      for i in self.game.objects.values():
        if isinstance(i,Port) and i.x == self.x and i.y == self.y:
          atPort = True
      if not atPort:
        for i in self.game.objects.values():
          if isinstance(i,Pirate):
            if i.x == self.x and i.y == self.y: 
              if i.owner == 2:
                self.game.Merchant2.pirateDied(i.homeBase)
              if i.owner == 3:
                self.game.Merchant3.pirateDied(i.homeBase)
              self.game.removeObject(i)
      self.game.removeObject(self)
    return True          

class Tile(Mappable):
  def __init__(self, game, id, x, y, type):
    self.game = game
    self.id = id
    self.x = x
    self.y = y
    self.type = type

  def toList(self):
    value = [
      self.id,
      self.x,
      self.y,
      self.type,
      ]
    return value

  def _distance(self, x, y):
    distance = 0
    if self.x > x:
      distance += self.x - x
    elif  x > self.x:
      distance += x - self.x
    if self.y > y:
      distance += self.y - y
    elif y > self.y:
      distance += y - self.y
    return distance

  @staticmethod
  def make(game, x, y, type):
    id = game.nextid
    game.nextid += 1
    #1 is water, 0 is land
    return Tile(game, id, x, y, type)
  
  def nextTurn(self):
    pass



class Treasure(Mappable):
  def __init__(self, game, id, x, y, gold):
    self.game = game
    self.id = id
    self.x = x
    self.y = y
    self.gold = gold

  def toList(self):
    value = [
      self.id,
      self.x,
      self.y,
      self.gold,
      ]
    return value

  @staticmethod
  def make(game, x, y, gold):
    id = game.nextid
    game.nextid += 1
    return Treasure(game, id, x, y, gold)
  
  def nextTurn(self):
    closest = self.game.mapSize*2
    for p in self.game.objects.values():
      if isinstance(p,Pirate):
        if p._distance(self.x,self.y) < closest:
          closest = p._distance(self.x,self.y)
    self.gold += sqrt(closest)
