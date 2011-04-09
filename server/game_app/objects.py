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
  def __init__(self, game, id, x, y, owner, health, strength, hasMoved, hasAttacked):
    self.game = game
    self.id = id
    self.x = x
    self.y = y
    self.owner = owner
    self.health = health
    self.strength = strength
    self.hasMoved = hasMoved
    self.hasAttacked = hasAttacked

  def toList(self):
    value = [
      self.id,
      self.x,
      self.y,
      self.owner,
      self.health,
      self.strength,
      self.hasMoved,
      self.hasAttacked,
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

  def _takeDamage(self, damage):
    self.health -= damage
    if self.health < 1 and self.id in self.game.objects:
      self.game.removeObject(self)



class Pirate(Unit):
  def __init__(self, game, id, x, y, owner, health, strength, hasMoved, hasAttacked):
    self.game = game
    self.id = id
    self.x = x
    self.y = y
    self.owner = owner
    self.health = health
    self.strength = strength
    self.hasMoved = hasMoved
    self.hasAttacked = hasAttacked

  def toList(self):
    value = [
      self.id,
      self.x,
      self.y,
      self.owner,
      self.health,
      self.strength,
      self.hasMoved,
      self.hasAttacked,
      ]
    return value

  @staticmethod
  def make(game, x, y, owner, health, strength):
    id = game.nextid
    game.nextid += 1
    # Placeholder for health and strength as 1, 1 respectively
    return Pirate(game, id, x, y, owner, health, strength, 0, 0)

  def nextTurn(self):
    self.hasMoved = 0
    self.hasAttacked = 0
    if self.game.playerID != self.owner:
      return True
    pass
    
  def takeDamage(self, pirate):
    self.health -= pirate.strength
    #If pirate is killed by the attack
    if self.health <= 0:
      #If the pirate did not kill himself, transfer gold to killing pirate... if it was a pirate that killed him
      if pirate.id != self.id and isinstance(pirate,Pirate):
        for i in self.game.objects.values():
          if isinstance(i,Treasure) and i.pirateID == self.id:
            iHasTreasure = False
            for j in self.game.objects.values():
              if isinstance(j,Treasure) and j.pirateID is pirate.id:
                j.amount += i.amount
                i.amount = 0
                self.game.removeObject(i)
                iHasTreasure = True
            if not iHasTreasure:
              i.pirateId = pirate.id
              i.x = pirate.x
              i.y = pirate.y
      #Otherwise the treasure becomes free game
      else:
        for i in self.game.objects.values():
          if isinstance(i,Treasure) and i.pirateID == self.id:
            i.pirateID = -1
      self.game.removeObject(self)
    return True
          
      

  def move(self, x, y):
    #Checking to see if moving a valid piece
    if self.owner != self.game.playerID:
      return "Tried to move a unit that is not yours"  
 
    #Checks to see if the unit has moved this turn
    #0 if has not moved
    if self.hasMoved > 0:
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
      #Check to see if the unit is moving into an enemy port
      elif isinstance(i,Port):
        if i.owner != self.owner and i.x == x and i.y == y: 
          return "Moving into an enemy port"
      #Checking if unit is moving onto water
      elif isinstance(i,Tile) and i.x is x and i.y is y and i.type is 1:
        isShip = False
        for j in self.game.objects.values():
          if isinstance(j,Ship) and j.x is x and j.y is y:
            #-1 is placeholder value for neutral shop. May need to be changed
            if j.owner is self.owner or j.owner is -1:
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
            if isinstance(j,Pirate) and j.x == x and j.y ==y:
              counter+=1
          #If this was the last pirate on board, the ship becomes neutral.
          if counter == 1:
            i.owner = -1          
            
    #Moves the unit and makes it unable to move until next turn
    self.hasMoved += 1
    self.x = x
    self.y = y
    #self.game.animations.append(['move', self.id, d])
    
    #Take control of a ship if you are the first one on it
    for i in self.game.objects.values():
      if isinstance(i,Ship) and i.x == x and i.y == y:
        if i.owner == -1:
          i.owner = self.owner

    #Moves the treasure this pirate is carrying to the new location
    for i in self.game.objects.values():
      if isinstance(i,Treasure):
        if self.id == i.pirateID:
          i.x = x
          i.y = y   
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
        if i.x == self.x and i.y == self.y:
          portPickup = True
          p = [i for i in self.game.objects.values() if isinstance(i,Player)]
          #Sets the owner of the pirate to eaither player 0 or 1
          if self.owner == 0:
            owner = 0
          else:
            owner = 1
          #Checks to make sure amount being withdrawn is less than that player has
          if amount <= p[owner].gold:          
            hasTreasure = False
            #check to see if the pirate already has treasure
            for j in self.game.objects.values():
              if isinstance(j,Treasure):
                #If the pirate does have treasure add it to that and deduct player's total
                if j.x == self.x and j.y == self.y and j.pirateID == self.ID:
                  j.amount += amount
                  p[owner].gold -= amount
                  hasTreasure = True
            #If the pirate did not have treasure we create a new thing of treasure for them
            if hasTreasure == False:
              treasure = i.make(game,self.x,self.y,self.ID,amount)
              game.addObject(treasure)
              p[owner].gold -= amount
              
    #If the pirate is not on a port and is trying to pickup Treasure
    if portPickup == False:
      for i in self.game.objects.values():
        if isinstance(i,Treasure):
          if i.x == self.x and i.y == self.y and i.pirateID == -1:
            #Check to make sure the amount being picked up isn't greater than its value
            if amount > i.amount:
              return "There isn't that much treasure!"
            #Checks to see if the pirate has treasure
            hasTreasure = False
            for j in self.game.objects.values():
              if isinstance(j,Treasure):
                #If the pirate has treasure, increase the value of the current trasure by amount and reduce from other treasure
                if j.pirateID == self.pirateID:
                  j.amount += amount
                  i.amount -= amount
                  #If that treasure has no value left, remove it
                  if i.amount <= 0:
                    self.game.removeObject(i)
                  hasTreasure = True
            #If the pirate does not have treasure
            if hasTreasure == False:     
              #If the pirate tries to pick up all of the treasure          
              if amount == i.amount:
                i.pirateID = self.ID        
            #Pirate picks up a portion of the treasure
            elif amount < i.amount:
              i.amount -= amount
              treasure = i.make(game,self.x,self.y,self.ID,amount)
              game.addObject(treasure)
            #Pirate tries to pick up more treasure than allowed                                              
    return True


  def dropTreasure(self, amount):
    if self.owner != self.game.playerID:
      return "Yarr!  Ye cannot trick me into dropin me treasure!  Yer not me captain!" 
    for i in self.game.objects.values():
      if isinstance(i,Treasure):
        #Locates the treasure being modified
        if i.pirateID == self.ID:
          if amount > i.amount:
             return "Not that much gold to drop"
          for j in self.game.objects.values():
            #if the treasure is being dropped on a port
            if isinstance(j,Port) and (j.owner == 0 or j.owner == 1):
              if i.x == j.x and i.y == j.y:
                #Increase gold of owner
                if self.owner == 0:
                  p = [i for i in self.game.objects.values() if isinstance(i,Player)]
                  p[0].gold += i.amount
                else:
                  p = [i for i in self.game.objects.values() if isinstance(i,Player)]
                  p[1].gold += i.amount
                #Decrement gold if only partially dropped
                if amount < i.amount:
                  i.amount -= amount
                #Remove if all dropped
                else:
                  self.game.removeObject(self.game.objects[i])
                return True
            #If there is already treasure at this location
            elif isinstance(j,Treasure):
              if i.x == j.x and i.y == j.y and i.id != j.id:
                #If they drop all of their treasure, remove the original
                #from the game
                #Else, simply increment the treasure on the ground and 
                #decrement that which the pirate is holding
                j.amount += i.amount
                if amount < i.amount:
                  i.amount -= amount                
                if amount == i.amount:
                  self.game.removeObject(self.game.objects[i])
          #If there was no previous treasure and there is no port          
          #If they dropped all of their trasure simply change owner to neutral
          if amount == i.amount:         
            i.pirateID = -1    
          #Dropping only a portion of their gold  
          #Decrement pirate's treasure amount, then create a new neutral treasure
          #at this location          
          else:
            i.amount -= amount
            treasure = i.make(game,self.x,self.y,-1,amount)
            game.addObject(treasure)
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
                p[0].gold -= self.game.portCost
                port = i.make(game,self.x,self.y,self.owner)
                game.addObject(port)
                return True
              else:
                return "Not enough gold to make this purchase"
            else:
              p = [i for i in self.game.objects.values() if isinstance(i,Player)]
              if p[1].gold >= self.game.portCost:
                p[1].gold -= self.game.portCost
                port = i.make(game,self.x,self.y,self.owner)
                game.addObject(port)
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
    
    elif self.hasAttacked is not 0:
      return "You've already attacked!"
    
    elif not (abs(self.x - Target.x)+abs(self.y  - Target.y) <= 1):
      return "That is too far away!"
    
    else:
      self.hasAttacked += 1
      #Optional Ally Pirate Auto Kill
      if isinstance(Target,Pirate) and Target.owner is self.owner:
        Target.health = 0
      
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
  def __init__(self, game, id, x, y, owner, health, strength, hasMoved, hasAttacked):
    self.game = game
    self.id = id
    self.x = x
    self.y = y
    self.owner = owner
    self.health = health
    self.strength = strength
    self.hasMoved = hasMoved
    self.hasAttacked = hasAttacked

  def toList(self):
    value = [
      self.id,
      self.x,
      self.y,
      self.owner,
      self.health,
      self.strength,
      self.hasMoved,
      self.hasAttacked,
      ]
    return value

  @staticmethod
  def make(game, x, y, owner, health, strength):
    id = game.nextid
    game.nextid += 1
    # Placeholder for health and strength as 1, 1 respectively
    return Ship(game, id, x, y, owner, health, strength, 0, 0)

  def nextTurn(self):
    self.hasMoved = 0
    self.hasAttacked = 0

  def move(self, x, y):
    #Check the owner of the ship before moving
    if self.owner != self.game.playerID:
      return "This be not yarr ship, ye swine!"
      
    if self.hasMoved >= self.game.shipSteps:
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
        if i.type != 1:
          return "Ships cannot walk!"
      
    #Makes sure there is no units at target location
    for i in self.game.objects.values():
      if isinstance(i,Unit):
        if i.x == x and i.y == y:
          return "There is already a unit at that location" 

    #Ship has passed all checks and it ready to move
    self.hasMoved += 1
    
    #Moving all treasure,pirates on the ship to the new location
    #Also moves the ship to the new location
    for i in self.game.objects.values():
      if isinstance(i,Pirate) and i.x == self.x and i.y == self.y:
        i.x = x
        i.y = y
      elif isinstance(i,Treasure) and i.x == self.x and i.y == self.y:
        i.x = x
        i.y = y
    self.x = x
    self.y = y
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
    self.hasAttacked += 1    
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
  def __init__(self, game, id, x, y, pirateID, amount):
    self.game = game
    self.id = id
    self.x = x
    self.y = y
    self.pirateID = pirateID
    self.amount = amount

  def toList(self):
    value = [
      self.id,
      self.x,
      self.y,
      self.pirateID,
      self.amount,
      ]
    return value

  @staticmethod
  def make(game, x, y, pirateID, amount):
    id = game.nextid
    game.nextid += 1
    return Treasure(game, id, x, y, pirateID, amount)
  
  def nextTurn(self):
    if self.pirateID == -1:
      closest = self.game.mapSize*3
      for p in self.game.objects.values():
        if isinstance(p,Pirate):
          if p._distance(self.x,self.y) < closest:
            closest = p._distance(self.x,self.y)
      self.amount += (self.amount * sqrt(closest))/100



