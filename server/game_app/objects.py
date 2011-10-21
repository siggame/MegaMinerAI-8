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
  def __init__(self, game, id, x, y, owner, spawnsLeft):
    self.game = game
    self.id = id
    self.x = x
    self.y = y
    self.owner = owner
    self.spawnsLeft = spawnsLeft

  def toList(self):
    value = [
      self.id,
      self.x,
      self.y,
      self.owner,
      self.spawnsLeft,
      ]
    return value

  def nextTurn(self):
    if self.owner == self.game.playerID:
      self.spawnsLeft = 1
    else:
      self.spawnsLeft = 0

  def spawn(self, level):
    player = self.game.objects.players[self.owner]
    cost = self.game.virusCost(level)
    if self.owner != self.game.playerID:
      return "You cannot spawn a virus at the opponents base"
    elif level < 0:
      return "Virus's must have a level greater than zero"
    elif player.cycles < cost:
      return "You don't have enough cycles to create this virus"
    elif self.spawnsLeft < 1:
      return "A base can only spawn one virus a turn"
    else:
      player.cycles -= cost
      self.spawnsLeft -= 1
      newVirus = self.game.addObject(Virus,[self.x,self.y,self.owner,level,0])
      self.game.animations.append(['Create', newVirus.id])
      return True

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
    if self.id == self.game.playerID:
      self.byteDollars += self.game.getScore(self.id)
      self.cycles += self.game.getIncome(self.id) 

  def talk(self, message):
    self.game.animations.append(['PlayerTalk', self.id, message])

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
  def __init__(self, game, id, x, y, owner, level, movesLeft, living=1):
    self.game = game
    self.id = id
    self.x = x
    self.y = y
    self.owner = owner
    self.level = level
    self.movesLeft = movesLeft
    self.living = living

  def toList(self):
    value = [
      self.id,
      self.x,
      self.y,
      self.owner,
      self.level,
      self.movesLeft,
      self.living,
      ]
    return value

  def nextTurn(self):
    if self.owner == self.game.playerID:
      self.movesLeft = 1
    else:
      self.movesLeft = 0

  def move(self, dx, dy):
    #You can't move a virus that belongs to the other player
    if self.owner != self.game.playerID:
      return "That virus is not yours to control"
    #You can't move if you have no moves left
    elif self.movesLeft <= 0:
      return "That virus has no more moves"
    #You can't move off the edge, the world is flat
    elif not (0 <= dx < self.game.width) or not (0 <=dy < self.game.height):
      return "Don't move off of the map"
    elif self.game.grid[dx][dy].owner == 3:
    #You can't move into a wall...the wall will win
      self.game.animations.append(['Crash', self.id, dx, dy])
      return "There is a wall in the way"
    #You can't move more than one space away
    elif abs(self.x-dx) + abs(self.y-dy) != 1:
      return "Units can only move to adjacent locations"
#Done? see if it works #TODO Handle units walking into friendly different level units

    for base in self.game.objects.bases:
      if base.x == dx and base.y == dy:
        self.game.animations.append(['Recycle', self.id, base.id])
        self.game.removeObject(self)
        return True

    for virus in self.game.objects.viruses:
     if virus.x == dx and virus.y == dy:
       if virus.owner == self.owner: 
         if virus.level != self.level:
           self.game.animations.append(['Crash', self.id, dx, dy])
           return("You cannot combine units of different levels")
         else:
           newVirus = self.game.addObject(Virus,[dx, dy, self.owner, self.level+1, 0])
           self.game.animations.append(['Combine', self.id, virus.id, newVirus.id])
           self.game.removeObject(virus)
           self.game.removeObject(self)
           print("When our powers combine!...we kill ourselves to make a slightly stronger virus",dx,dy) ###
           return True
       #moving a virus onto an enemy virus, conflict!!
       else:
         self.game.animations.append(['Combat',self.id,virus.id])
         if virus.level > self.level:
           self.game.removeObject(self)
           return True
         elif self.level > virus.level:
           self.game.removeObject(virus)
           # NO return because the move should still happen
        #if you're evenly matched, a great battle ensues, and you both die
         elif virus.level == self.level:
           self.game.removeObject(virus)
           self.game.removeObject(self)
           print("two evenly matched viruses enter, no one leaves ",dx,dy)###
           return True
    self.x = dx
    self.y = dy
    self.game.grid[dx][dy].owner = self.owner
    self.movesLeft-=1
    return True
  
  def talk(self, message):
    self.game.animations.append(['VirusTalk',self.id,message])
