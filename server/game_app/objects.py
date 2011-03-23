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
    if x > self.game.boardX -1:
      return "Stepping off the world"
    elif y > self.game.boardY -1:
      return "Stepping off the world"
    elif y < 0:
      return "Stepping off the world"
    elif x < 0:
      return "Stepping off the world"

    #Check to see if the unit is moving into an enemy
    for i in self.game.objects.values():
      if isinstance(i,Unit):
        if i.owner != self.owner and i.x == x and i.y == y:
          return "Enemy at that location"
      #Check to see if the unit is moving into an enemy port
      elif isinstance(i,Port):
        if i.owner != self.owner and i.x == x and i.y == y: 
          return "Moving into an enemy port"
      #Checking if unit is on land 
      elif isinstance(i,Tile):
        if i.x == x and i.y == y:
          isShip = False
          for j in self.game.objects.values():
            if isinstance(j,Ship):
  
              #-1 is placeholder value for neutral shop. May need to be changed
              if j.owner == self.owner or -1:
                isShip = True

          if i.type == 'w' and isShip != True:
            return "Pirates cannot swim!"

    #Moves the unit and makes it unable to move until next turn
    self.hasMoved += 1
    self.x = x
    self.y = y
    #self.game.animations.append(['move', self.id, d])

    #Moves the treasure this pirate is carrying to the new location
    for i in self.game.objects.values():
      if isinstance(i,Treasure):
        if self.id == i.pirateID:
          i.x = x
          i.y = y
    
    return True

  def talk(self, message):
    pass


  def pickupTreasure(self, amount):
    for i in self.game.objects.values():
      if isinstance(i,Treasure):
        if i.x == self.x and i.y == self.y and i.pirateID == -1:
          #Pirate picks up all of the treasure
          if amount == i.amount:
            i.pirateID = self.ID
          #Pirate picks up a portion of the treasure
          elif amount < i.amount:
            i.amount -= amount
            treasure = i.make(game,self.x,self.y,self.ID,amount)
            game.addObject(treasure)
          #Pirate tries to pick up more treasure than allowed
          else:
            return "There isn't that much treasure!"
    return True


  def dropTreasure(self, amount):
    for i in self.game.objects.values():
      if isinstance(i,Treasure):
        if i.pirateID == self.ID:
          #If pirate tries to drop all of his treasure
          if amount == i.amount:
            #If they drop the treasure on a port
            for j in self.game.objects.values():
              if isinstance(j,Port):
                if i.x == j.x and i.y == j.y:
                  if self.owner == 0:
                    self.game.player0Gold += i.amount
                  else:
                    self.game.player1Gold += i.amount
                    self.game.removeObject(self.game.objects[i])
                  return True
                  #TODO: Increases a players total gold amount by i.amount
            i.pirateID = -1
            
          #Pirate drops a portion of his treasure
          elif amount < i.amount:
            i.amount -= amount
            treasure = i.make(game,self.x,self.y,-1,amount)
            game.addObject(treasure)
          #Pirate tries to drop more than he has
          else:
            return "Not enough treasure to drop!"
    return True
            
  def buildPort(self):
    for i in self.game.objects.values():
      if isinstance(i, Tile):
        if i._distance(self.x,self.y): #Not sure about this
          if i.type == 1:
            if self.onwer == 0:
              if game.self.player0Gold >= portCost:
                game.self.player0Gold -= portCost
                port = i.make(game,self.x,self.y,self.owner)
                game.addObject(port)
                return True
              else:
                return "Not enough gold to make this purchase"
            else:
              if game.self.player1Gold >= portCost:
                game.self.player1Gold -= portCost
                port = i.make(game,self.x,self.y,self.owner)
                game.addObject(port)
                return True
              else:
                return "Not enough gold to make this purchase"
          else:
           return "No water connected to this location"

  def attack(self, Target):
    pass



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
    if self.owner == 0:
      if player0Gold >= pirateCost:
        player0Gold -= pirateCost
        pirate = pirate.make(game, self.x, self.y, self.owner, 10, 2) #placeholder values
        game.addObject(pirate)
        return True
      else:
        return "Not enough gold for that unit"
    else:
      if player1Gold >= pirateCost:
        player1Gold -= pirateCost
        pirate = pirate.make(game, self.x, self.y, self.owner, 10, 2) #placeholder values
        game.addObject(pirate)
        return True
      else:
        return "Not enough gold for that unit"

  def createShip(self):
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
    pass

  def move(self, x, y):
    return True
    

  def talk(self, message):
    pass

  def attack(self, Target):
    pass



class Tile(Mappable):
  def __init__(self, game, id, x, y, type):
    self.game = game
    self.id = id
    self.x = x
    self.y = y
    self.type = type #1 for water, 0 for land

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
    pass
