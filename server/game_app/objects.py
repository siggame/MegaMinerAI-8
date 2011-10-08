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
#    player = self.game.objects.players[
    #TODO Award money to the player
      #don't actually know how money is awarded, read game concept
    #TODO Award points to the player
      #will be the size of the set of bases under your control, this is similar to the function tilepath.
      #could just make a self attribute from tilepath to return the size of the paths, add that to points
    self.byteDollars += len(self.game.path)

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
    #TODO when a virus moves over a tile it turns the tile to the player's type/ownership
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
  #!!!!!!!!!!!!!!!!!!!!!!!!!!!!2am code, beware!!!!!!!!!!!!!!!!!!!11111
    for i in self.game.objects.viruses:
      if i.owner is self.owner and i.x is x and i.y is y:
        #moving a unit onto a friendl of a different level is a no no
        if i.level is not self.level:
          return "You can't move your unit to another of yours of different level"
        #moving a unit onto a friendly of same level makes a new 
        #virus of a higher level, gets rid of other two. LEVEL UP!
        elif i.level is self.level:
         newLevel = i.level+1
         addObject('Virus',[x,y,newLevel])
         removeObject(self.game.object.Virus)
         removeObject(self.game.object.Virus)#do we have a removeObject function? found it, did I use it correctly?
         return "When our powers combine!...we kill ourselves to make a slightly stronger virus"
        #moving a virus onto an enemy virus, conflict!!
      elif i.owner is not self.owner and i.x is x and i.y is y:
        #TODO return some money for removed Viruses to player 
        #if they're stronger, you weaken them, they kill you
        if i.level > self.level:
          i.level -= self.level
          removeObject(self,'Virus')
          return "two uneven viruses meet, you weakened him, but your virus died"
        #if you're stronger, they weaken you, you kill them
        elif i.level < self.level:
          self.level -= i.level
          removeObject(self.game.object.Virus)
          return "two uneven viruses meet, you are weaker, but your foe is dead"
        #if you're evenly matched, a great battle ensues, and you both die
        elif i.level is self.level:
          removeObject(self.game.object.Virus)
          removeObject(self.game.object.Virus)
          return "two evenly matched viruses enter, no one leaves"
#Done? need to test    #TODO Handle units walkint into friendly same level units
#Done? need to test    #TODO Handle units walking into enemy units ...conflict!
#compiles, need to test
    #TODO Each case has animations
        else:
          self.x = x
          self.y = y
          return "Successful, uneventful move"
#don't know if I need all the returns, but might help debugging, plus they're fun to write, and easy to remove if need be
  def talk(self, message):
    self.game.animations.append(['VirusTalk',self.id,message])



