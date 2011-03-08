# -*- python -*-

from library import library

from ExistentialError import ExistentialError

class GameObject(object):
  def __init__(self, ptr):
    from BaseAI import BaseAI
    self.ptr = ptr
    self.iteration = BaseAI.iteration


##An object that exists on the grid
class Mappable(GameObject):
  def __init__(self, ptr):
    from BaseAI import BaseAI
    self.ptr = ptr
    self.iteration = BaseAI.iteration
    
    self.id = library.mappableGetId(ptr)

  ##Unique Identifier
  def getId(self):
    self.validify()
    return library.mappableGetId(self.ptr)

  ##The X position of the top left corner of this object.  X is horizontal
  def getX(self):
    self.validify()
    return library.mappableGetX(self.ptr)

  ##The Y position of the top left corner of this object.  Y is vertical
  def getY(self):
    self.validify()
    return library.mappableGetY(self.ptr)


  def __str__(self):
    self.validify()
    ret = ""
    ret += "id: %s\n" % self.getId()
    ret += "x: %s\n" % self.getX()
    ret += "y: %s\n" % self.getY()
    return ret

##Generic Unit
class Unit(Mappable):
  def __init__(self, ptr):
    from BaseAI import BaseAI
    self.ptr = ptr
    self.iteration = BaseAI.iteration
    
    self.id = library.unitGetId(ptr)

  ##Move the unit to the designated X and Y coordinates
  def move(self, x, y):
    self.validify()
    return library.unitMove(self.ptr, x, y)

  ##Allows a unit to display a message to the screen.
  def talk(self, message):
    self.validify()
    return library.unitTalk(self.ptr, message)

  ##Unique Identifier
  def getId(self):
    self.validify()
    return library.unitGetId(self.ptr)

  ##The X position of the top left corner of this object.  X is horizontal
  def getX(self):
    self.validify()
    return library.unitGetX(self.ptr)

  ##The Y position of the top left corner of this object.  Y is vertical
  def getY(self):
    self.validify()
    return library.unitGetY(self.ptr)

  ##The owner of the unit
  def getOwner(self):
    self.validify()
    return library.unitGetOwner(self.ptr)

  ##health of the unit
  def getHealth(self):
    self.validify()
    return library.unitGetHealth(self.ptr)

  ##attacking strength of the unit
  def getStrength(self):
    self.validify()
    return library.unitGetStrength(self.ptr)


  def __str__(self):
    self.validify()
    ret = ""
    ret += "id: %s\n" % self.getId()
    ret += "x: %s\n" % self.getX()
    ret += "y: %s\n" % self.getY()
    ret += "owner: %s\n" % self.getOwner()
    ret += "health: %s\n" % self.getHealth()
    ret += "strength: %s\n" % self.getStrength()
    return ret

##A generic pirate
class Pirate(Unit):
  def __init__(self, ptr):
    from BaseAI import BaseAI
    self.ptr = ptr
    self.iteration = BaseAI.iteration
    
    self.id = library.pirateGetId(ptr)

  def validify(self):
    from BaseAI import BaseAI
    #if this class is pointing to an object from before the current turn it's probably
    #somewhere else in memory now
    if self.iteration == BaseAI.iteration:
      return True
    for i in BaseAI.pirates:
      if i.id == self.id:
        self.ptr = i.ptr
        self.iteration = BaseAI.iteration
        return True
    raise ExistentialError()
  ##Move the unit to the designated X and Y coordinates
  def move(self, x, y):
    self.validify()
    return library.pirateMove(self.ptr, x, y)

  ##Allows a unit to display a message to the screen.
  def talk(self, message):
    self.validify()
    return library.pirateTalk(self.ptr, message)

  ##Allows the pirate to pickup treasure on the ground.
  def pickupTreasure(self, amount):
    self.validify()
    return library.piratePickupTreasure(self.ptr, amount)

  ##Allows the pirate to drop treasure on the groud.
  def dropTreasure(self, amount):
    self.validify()
    return library.pirateDropTreasure(self.ptr, amount)

  ##Attempt to attack the given unit
  def attack(self, Target):
    self.validify()
    if not isinstance(Target, Unit):
      raise TypeError('Target should be of [Unit]')
    Target.validify()
    return library.pirateAttack(self.ptr, Target.ptr)

  ##Unique Identifier
  def getId(self):
    self.validify()
    return library.pirateGetId(self.ptr)

  ##The X position of the top left corner of this object.  X is horizontal
  def getX(self):
    self.validify()
    return library.pirateGetX(self.ptr)

  ##The Y position of the top left corner of this object.  Y is vertical
  def getY(self):
    self.validify()
    return library.pirateGetY(self.ptr)

  ##The owner of the unit
  def getOwner(self):
    self.validify()
    return library.pirateGetOwner(self.ptr)

  ##health of the unit
  def getHealth(self):
    self.validify()
    return library.pirateGetHealth(self.ptr)

  ##attacking strength of the unit
  def getStrength(self):
    self.validify()
    return library.pirateGetStrength(self.ptr)


  def __str__(self):
    self.validify()
    ret = ""
    ret += "id: %s\n" % self.getId()
    ret += "x: %s\n" % self.getX()
    ret += "y: %s\n" % self.getY()
    ret += "owner: %s\n" % self.getOwner()
    ret += "health: %s\n" % self.getHealth()
    ret += "strength: %s\n" % self.getStrength()
    return ret

##A generic port
class Port(Mappable):
  def __init__(self, ptr):
    from BaseAI import BaseAI
    self.ptr = ptr
    self.iteration = BaseAI.iteration
    
    self.id = library.portGetId(ptr)

  def validify(self):
    from BaseAI import BaseAI
    #if this class is pointing to an object from before the current turn it's probably
    #somewhere else in memory now
    if self.iteration == BaseAI.iteration:
      return True
    for i in BaseAI.ports:
      if i.id == self.id:
        self.ptr = i.ptr
        self.iteration = BaseAI.iteration
        return True
    raise ExistentialError()
  ##Creates a Pirate at the calling Port
  def createPirate(self):
    self.validify()
    return library.portCreatePirate(self.ptr)

  ##Creates a Ship at the calling Port
  def createShip(self):
    self.validify()
    return library.portCreateShip(self.ptr)

  ##Unique Identifier
  def getId(self):
    self.validify()
    return library.portGetId(self.ptr)

  ##The X position of the top left corner of this object.  X is horizontal
  def getX(self):
    self.validify()
    return library.portGetX(self.ptr)

  ##The Y position of the top left corner of this object.  Y is vertical
  def getY(self):
    self.validify()
    return library.portGetY(self.ptr)

  ##The ownder of the port
  def getOwner(self):
    self.validify()
    return library.portGetOwner(self.ptr)


  def __str__(self):
    self.validify()
    ret = ""
    ret += "id: %s\n" % self.getId()
    ret += "x: %s\n" % self.getX()
    ret += "y: %s\n" % self.getY()
    ret += "owner: %s\n" % self.getOwner()
    return ret

##A generic ship
class Ship(Unit):
  def __init__(self, ptr):
    from BaseAI import BaseAI
    self.ptr = ptr
    self.iteration = BaseAI.iteration
    
    self.id = library.shipGetId(ptr)

  def validify(self):
    from BaseAI import BaseAI
    #if this class is pointing to an object from before the current turn it's probably
    #somewhere else in memory now
    if self.iteration == BaseAI.iteration:
      return True
    for i in BaseAI.ships:
      if i.id == self.id:
        self.ptr = i.ptr
        self.iteration = BaseAI.iteration
        return True
    raise ExistentialError()
  ##Move the unit to the designated X and Y coordinates
  def move(self, x, y):
    self.validify()
    return library.shipMove(self.ptr, x, y)

  ##Allows a unit to display a message to the screen.
  def talk(self, message):
    self.validify()
    return library.shipTalk(self.ptr, message)

  ##Attempt to attack the given unit
  def attack(self, Target):
    self.validify()
    if not isinstance(Target, Unit):
      raise TypeError('Target should be of [Unit]')
    Target.validify()
    return library.shipAttack(self.ptr, Target.ptr)

  ##Unique Identifier
  def getId(self):
    self.validify()
    return library.shipGetId(self.ptr)

  ##The X position of the top left corner of this object.  X is horizontal
  def getX(self):
    self.validify()
    return library.shipGetX(self.ptr)

  ##The Y position of the top left corner of this object.  Y is vertical
  def getY(self):
    self.validify()
    return library.shipGetY(self.ptr)

  ##The owner of the unit
  def getOwner(self):
    self.validify()
    return library.shipGetOwner(self.ptr)

  ##health of the unit
  def getHealth(self):
    self.validify()
    return library.shipGetHealth(self.ptr)

  ##attacking strength of the unit
  def getStrength(self):
    self.validify()
    return library.shipGetStrength(self.ptr)


  def __str__(self):
    self.validify()
    ret = ""
    ret += "id: %s\n" % self.getId()
    ret += "x: %s\n" % self.getX()
    ret += "y: %s\n" % self.getY()
    ret += "owner: %s\n" % self.getOwner()
    ret += "health: %s\n" % self.getHealth()
    ret += "strength: %s\n" % self.getStrength()
    return ret

##A basic tile
class Tile(Mappable):
  def __init__(self, ptr):
    from BaseAI import BaseAI
    self.ptr = ptr
    self.iteration = BaseAI.iteration
    
    self.id = library.tileGetId(ptr)

  def validify(self):
    from BaseAI import BaseAI
    #if this class is pointing to an object from before the current turn it's probably
    #somewhere else in memory now
    if self.iteration == BaseAI.iteration:
      return True
    for i in BaseAI.tiles:
      if i.id == self.id:
        self.ptr = i.ptr
        self.iteration = BaseAI.iteration
        return True
    raise ExistentialError()
  ##Unique Identifier
  def getId(self):
    self.validify()
    return library.tileGetId(self.ptr)

  ##The X position of the top left corner of this object.  X is horizontal
  def getX(self):
    self.validify()
    return library.tileGetX(self.ptr)

  ##The Y position of the top left corner of this object.  Y is vertical
  def getY(self):
    self.validify()
    return library.tileGetY(self.ptr)

  ##land = 0, water = 1
  def getType(self):
    self.validify()
    return library.tileGetType(self.ptr)


  def __str__(self):
    self.validify()
    ret = ""
    ret += "id: %s\n" % self.getId()
    ret += "x: %s\n" % self.getX()
    ret += "y: %s\n" % self.getY()
    ret += "type: %s\n" % self.getType()
    return ret

##A treasure
class Treasure(Mappable):
  def __init__(self, ptr):
    from BaseAI import BaseAI
    self.ptr = ptr
    self.iteration = BaseAI.iteration
    
    self.id = library.treasureGetId(ptr)

  def validify(self):
    from BaseAI import BaseAI
    #if this class is pointing to an object from before the current turn it's probably
    #somewhere else in memory now
    if self.iteration == BaseAI.iteration:
      return True
    for i in BaseAI.treasures:
      if i.id == self.id:
        self.ptr = i.ptr
        self.iteration = BaseAI.iteration
        return True
    raise ExistentialError()
  ##Unique Identifier
  def getId(self):
    self.validify()
    return library.treasureGetId(self.ptr)

  ##The X position of the top left corner of this object.  X is horizontal
  def getX(self):
    self.validify()
    return library.treasureGetX(self.ptr)

  ##The Y position of the top left corner of this object.  Y is vertical
  def getY(self):
    self.validify()
    return library.treasureGetY(self.ptr)

  ##The pirate carrying this treasure
  def getPirate(self):
    self.validify()
    return library.treasureGetPirate(self.ptr)


  def __str__(self):
    self.validify()
    ret = ""
    ret += "id: %s\n" % self.getId()
    ret += "x: %s\n" % self.getX()
    ret += "y: %s\n" % self.getY()
    ret += "pirate: %s\n" % self.getPirate()
    return ret
