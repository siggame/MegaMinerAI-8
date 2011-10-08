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



class Base(Mappable):
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

  def nextTurn(self):
    pass

    #TODO make the virus cost something
  def spawn(self, level):
    if self.objects.Player.cycles < level**self.scalecost:
      return "You don't have enough cycles to create this virus"
    else
      self.addObject(Virus, [self.x, self.y, self.owner, level, 0])


class Player:
  def __init__(self, game, id, playerName, byteDollars, cycles):
    self.game = game
    self.id = id
    self.playerName = playerName
    self.byteDollars = byteDollars
    self.cycles = cycles

  def toList(self):
    value = [
      self.id,
      self.playerName,
      self.byteDollars,
      self.cycles,
      ]
    return value

  def nextTurn(self):
    pass

  def talk(self, message):
    self.game.animations.append(['talk',self.id,message])
    return true



class Tile(Mappable):
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

  def nextTurn(self):
    pass



class Virus(Mappable):
  def __init__(self, game, id, x, y, owner, level, movesLeft):
    self.game = game
    self.id = id
    self.x = x
    self.y = y
    self.owner = owner
    self.level = level
    self.movesLeft = movesLeft

  def toList(self):
    value = [
      self.id,
      self.x,
      self.y,
      self.owner,
      self.level,
      self.movesLeft,
      ]
    return value

  def nextTurn(self):
    self.movesLeft = 1
    return

  def move(self, x, y):
    if self.owner != self.game.playerID:
      return "That virus is not yours to control"
    if self.movesLeft <= 0:
      return "That virus has no more moves"
    if self.game.grid[x][y].owner == 3:
      return "There is a wall in the way"
    if abs(self.x-x) + abs(self.y-y) > 1:
      return "Units can only move to adjacent locations"
    #TODO Handle units walking to each other
    self.x = x
    self.y = y
    
  def talk(self, message):
    pass



