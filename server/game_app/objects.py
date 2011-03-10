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
    pass

  def talk(self, message):
    pass



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



