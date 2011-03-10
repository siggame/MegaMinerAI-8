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
  def __init__(self, game, id, x, y, owner, health, strength):
    self.game = game
    self.id = id
    self.x = x
    self.y = y
    self.owner = owner
    self.health = health
    self.strength = strength

  def toList(self):
    value = [
      self.id,
      self.x,
      self.y,
      self.owner,
      self.health,
      self.strength,
      ]
    return value

  def nextTurn(self):
    pass

  def move(self, x, y):

    #Checking to see if moving a valid piece
    if self.owner != self.game.playerID:
      return: "Tried to move a unit that is not yours"

    #Checking to make sure the unit is in the bounds of the map
    if self.x + x > self.game.boardX -1:
      return "Stepping off the world"
    elif self.y + y > self.game.boardY -1:
      return "Stepping off the world"
    elif self.y - y < 0:
      return "Stepping off the world"
    elif self.x - x < 0:
      return "Stepping off the world"

    #Check to see if the unit is moving into an enemy
    for i in self.game.objects.values():
      if isinstance(i,Unit):
        if Unit.owner != self.owner:
          return "Enemy at that location"

    #Check to see if the unit is moving into an enemy port
    for i in self.game.objects.values():
      if isinstance(i,Port):
        if Port.owner != self.owner:
          return "Moving into an enemy port"
    
    self.game.animations.append(['move', self.id, d])
    self._move(x, y)

    return True

  def talk(self, message):
    self.game.animations.append(['talk', self.id, message])
    return true

  def _distance(self, target):
    x = 0
    y = 0
    if self.x > target.x + target.size-1:
      x = self.x - (target.x + target.size-1)
    elif target.x > self.x + self.size-1:
      x = target.x - (self.x + self.size-1)
    if self.y > target.y + target.size-1:
      y = self.y - (target.y + target.size-1)
    elif target.y > self.y + self.size-1:
      y = target.y - (self.y + self.size-1)
    return x + y

  def _takeDamage(self, damage):
    self.health -= damage
    if self.health < 1 and self.id in self.game.objects:
      self.game.removeObject(self)

class Pirate(Unit):
  def __init__(self, game, id, x, y, owner, health, strength):
    self.game = game
    self.id = id
    self.x = x
    self.y = y
    self.owner = owner
    self.health = health
    self.strength = strength

  def toList(self):
    value = [
      self.id,
      self.x,
      self.y,
      self.owner,
      self.health,
      self.strength,
      ]
    return value

  @staticmethod
  def make(game, x, y, owner):
    id = game.nextid
    game.nextid += 1
    # Placeholder for health and strength as 1, 1 respectively
    return Pirate(game, id, x, y, owner, 1, 1)

  def nextTurn(self):
    pass

  def move(self, x, y):
    pass
   
    

  def talk(self, message):
    pass

  def pickupTreasure(self, amount):
    pass

  def dropTreasure(self, amount):
    pass

  def buildPort(self):
    pass

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
    pass

  def createShip(self):
    pass



class Ship(Unit):
  def __init__(self, game, id, x, y, owner, health, strength):
    self.game = game
    self.id = id
    self.x = x
    self.y = y
    self.owner = owner
    self.health = health
    self.strength = strength

  def toList(self):
    value = [
      self.id,
      self.x,
      self.y,
      self.owner,
      self.health,
      self.strength,
      ]
    return value
    
  @staticmethod
  def make(game, x, y, owner):
    id = game.nextid
    game.nextid += 1
    # Placeholder for health and strength as 1, 1 respectively
    return Ship(game, id, x, y, owner, 1, 1)
  
  def nextTurn(self):
    pass

  def move(self, x, y):
    pass

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
    self.type = type

  def toList(self):
    value = [
      self.id,
      self.x,
      self.y,
      self.type,
      ]
    return value
  
  @staticmethod
  def make(game, x, y, type):
    id = game.nextid
    game.nextid += 1
    #'w' is water, 'l' is land
    return Tile(game, id, x, y, type)
  
  def nextTurn(self):
    pass



class Treasure(Mappable):
  def __init__(self, game, id, x, y, pirate):
    self.game = game
    self.id = id
    self.x = x
    self.y = y
    self.pirate = pirate

  def toList(self):
    value = [
      self.id,
      self.x,
      self.y,
      self.pirate,
      ]
    return value
  
  @staticmethod
  def make(game, x, y, pirateID):
    id = game.nextid
    game.nextid += 1
    return Treasure(game, id, x, y, pirateID)
  
  def nextTurn(self):
    pass



