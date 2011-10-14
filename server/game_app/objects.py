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
   return "base next turn called"

#Done, wait to see if it works    #TODO make the virus cost something
#spawn keeps getting denied 
  def spawn(self, level):
    player = self.game.objects.players[self.owner]
    cost = self.game.baseCost*self.game.scaleCost**level
    if player.cycles < cost:
 #     print('Cannot afford virus')
      return "You don't have enough cycles to create this virus"
    elif player.cycles >= cost:
  #might allow for player strategy; neg virus will be cheap, but lose every fight
     if level <0:
 #      print('tried making neg virus')
       return "You can't create a virus with a negative level"
     else:
      player.cycles -= cost
      self.game.addObject(Virus,[self.x,self.y,self.owner,level,0])
      self.game.animations.append(['Create',self.game.objects.viruses[-1].id])
      return True     
    else:
      return "wat"

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
    #TODO Award money to the player
      #don't actually know how money is awarded, read game concept
    #TODO Award points to the player
#Done-ish, won't mean anything till we get path up 
      #will be the size of the set of bases under your control, this is similar to the function tilepath.
      #could just make a self attribute from tilepath to return the size of the paths, add that to points
   # print('!!!!!player next turn!!!!!!!! ->',self.id)#game.objects.players[self.id])
    self.byteDollars += len(self.game.path) #-> should be someting like this
    self.cycles += 2000 #this is for testing, so we can keep making viruses

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

  def move(self, dx, dy):
#Done? need to test #TODO when a virus moves over a tile it turns the tile to the player's type/ownership
    #You can't move a virus that belongs to the other player
    if self.owner != self.game.playerID:
#      print("That virus is not yours to control")
      return "That virus is not yours to control"
    #You can't move if you have no moves left
    if self.movesLeft <= 0:
      print("That virus has no more moves")
      return "That virus has no more moves"
    #You can't move off the edge, the world is flat
    if not (0 <= dx < self.game.width) or not (0 <=dy < self.game.height):
      print("Don't move off of the map")
      return "Don't move off of the map"
    if self.game.grid[dx][dy].owner == 3:
    #You can't move into a wall...the wall will win
#might work, still worth looking into#TODO how to pass Crash grid x and y, not sure if what I have works
      self.game.animations.append(['Crash',self.id,self.game.grid[dx],self.game.grid[dy]])
      print("There is a wall in the way")
      return "There is a wall in the way"
    #You can't move more than one space away
    if abs(self.x-dx) + abs(self.y-dy) > 1:
      print("Units have move range of 1")
      return "Units can only move to adjacent locations"
#Done? see if it works #TODO Handle units walking into friendly different level units
    for i in self.game.objects.bases:
      if i.x == dx and i.y == dy:
        print("You can't move onto a base",dx,dy)
        return "You cannot move onto a base, back to the field soldier!"
    for i in self.game.objects.viruses:
     if i.owner == self.owner: 
      print("i.owner is self.owner")
      if i.x == dx:
       print("i.x is dx")
       if i.y == dy:
        print("i.y is dy")
        #moving a unit onto a friendly of a different level is a no no
        if i.level != self.level:
          self.game.animations.append(['Crash',self.id,i.x,i.y])
          print("You can't move your unit to another of yours of different level",dx,dy)
          return("You can't move your unit to another of yours of different level") ###
        #moving a unit onto a friendly of same level makes a new 
        #virus of a higher level, gets rid of other two. LEVEL UP!
        elif i.level == self.level:
#Done? needs testing #TODO look into animations
          self.game.addObject(Virus,[dx,dy,i.owner,self.level+1,0])
          self.game.animations.append(['Combine',self.id,i.id,self.game.objects.viruses[-1].id])           
#Done? needs testing #TODO look into removeObject
          self.game.removeObject(i)
          self.game.removeObject(self)#do we have a removeObject function? found it, did I use it correctly?
          print("When our powers combine!...we kill ourselves to make a slightly stronger virus",dx,dy) ###
          return True
        #moving a virus onto an enemy virus, conflict!!
     elif i.owner != self.owner:
      print("i.owner isn't self.owner") 
      if i.x == dx:
       print("i.x is dx")
       if i.y == dy:
        print("i.y is dy")
      # print('MY NAME IS VIRUSO MONTOYA, PREPARE TO DIE') don't have the heart to kill Viruso Montoya/remove this comment
#TODO return some money for removed Viruses to player 
        #if they're stronger, you weaken them, they kill you
        if i.level > self.level:
          self.game.animations.append(['Combat',self.id,i.id])
          i.level -= self.level
          self.game.removeObject(self)
          print("two uneven viruses meet, you weakened him, but your virus died ",dx,dy) ###
          return True
        #if you're stronger, they weaken you, you kill them
        elif i.level < self.level:
          self.game.animations.append(['Combat',self.id,i.id])
          self.level -= i.level
          self.game.removeObject(i)
          self.game.grid[dx][dy].owner = self.owner
          self.movesLeft-=1
          print("two uneven viruses meet, you are weaker, but your foe is dead ",dx,dy)###
          return True
        #if you're evenly matched, a great battle ensues, and you both die
        elif i.level == self.level:
          self.game.animations.append(['Combat',self.id,i.id])# WHY DO YOU BREAK TEH GAME?!
          self.game.removeObject(i)
          self.game.removeObject(self)
          print("two evenly matched viruses enter, no one leaves ",dx,dy)###
          return True
#Done? need to test    #TODO Handle units walkint into friendly same level units
#Done? need to test    #TODO Handle units walking into enemy units ...conflict!
#Done? need to test    #TODO Each case has animations
      else:
        self.game.animations.append(['Move',self.id,self.x,self.y])
        self.x = dx
        self.y = dy
        self.game.grid[dx][dy].owner = self.owner
        self.movesLeft-=1
#        print( "Successful, uneventful move",dx,dy)###
        return True
    return("got to end of function without hitting cases...wat")###
#Done? need to test #TODO make it so an enemy virus can't move onto a base 
  
  def talk(self, message):
    self.game.animations.append(['VirusTalk',self.id,message])



