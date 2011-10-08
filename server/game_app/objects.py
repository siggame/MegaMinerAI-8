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

#Done, wait to see if it works    #TODO make the virus cost something
  def spawn(self, level):
    player = self.game.objects.players[self.owner]
    cost = self.game.baseCost*self.game.scaleCost**level
    if player.cycles < cost:
      return "You don't have enough cycles to create this virus"
    else:
      self.game.addObject(Virus, [self.x, self.y, self.owner, level, 0])
      player.cycles -= cost

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
    player = self.game.objects.players[self.owner]
    #TODO Award money to the player
      #don't actually know how money is awarded, read game concept
    #TODO Award points to the player
      #will be the size of the set of bases under your control, this is similar to the function tilepath.
    pass

  def talk(self, message):
    self.game.animations.append(['PlayerTalk',self.id,message])


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
    if self.owner == self.game.playerID:
      self.movesLeft = 1
    return

  def move(self, x, y):
    #You can't move a virus that belongs to the other player
    if self.owner != self.game.playerID:
      return "That virus is not yours to control"
    #You can't move if you have no moves left
    if self.movesLeft <= 0:
      return "That virus has no more moves"
    #You can't move off the edge, the world is flat
    if not (0 <= x < self.game.width) or not (0 <=y < self.game.height):
      return "Don't move off of the map"
    if self.game.grid[x][y].owner == 3:
    #You can't move into a wall...the wall will win
      return "There is a wall in the way"
    #You can't move more than one space away
    if abs(self.x-x) + abs(self.y-y) > 1:
      return "Units can only move to adjacent locations"
    #TODO Handle units walking into friendly different level units
    #TODO Handle units walkint into friendly same level units
    #TODO Handle units walking into enemy units ...conflict!
    #TODO Each case has animations
    self.x = x
    self.y = y
    
  def talk(self, message):
    self.game.animations.append(['VirusTalk',self.id,message])



