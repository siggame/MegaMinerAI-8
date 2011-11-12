#-*-python-*-
from BaseAI import BaseAI
from GameObject import *
import random

class path:
 direction1 = 1
 direction2 = 1
 direction3 = 1
 count = 0
#3 bases

class waters:
 shark1 = 0
 shark2 = 0
 shark3 = 0
 fishing = 0
 shiver = 0
 
 def checkwater(self,toplevel):
  print("shark in the water, our shark")
  for shark in AI.viruses:
   if shark.getLevel() == toplevel:
    self.shiver += 1
  if self.shiver <= 3:
   return True 
  


class AI(BaseAI):
 
 
 """The class implementing gameplay logic."""
 @staticmethod
 def username():
    return "Kellogg"
         
 @staticmethod
 def password():
   return "password"
                  
 def init(self):
    print("HELLO MOTTO")
    pass
                        
 def end(self):
    print("END OF ALL HOPE")
    pass

 
 

 def check(self,viruso,x,y):
   print("calling check!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")
   if viruso.getOwner() != self.playerID():
    print("not your virus")
    return False
    
   if abs(viruso.getX()-x) + abs(viruso.getY()-y) !=1:
    print("too far away")
    return False
    
   for tile in self.tiles:
    if tile.getX() == x and tile.getY() == y and tile.getOwner == 3:
      print("moving into  a wall")
      return False
   
   if x<0 or x>40:
    print("moving off of the map")
    return False
   elif y<0 or y>20:
    print("moving off of the map")
    return False
            
#   if viruso.getMovesLeft == 0:
#    print("virus has no moves left")
#    return False
   
   for base in self.bases:
    if base.getX() == x and base.getY() == y:
     print("can't move onto a base")
     return False
    
   for virus in self.viruses:
    if virus.getX() == x and virus.getY() == y:
     if virus.getOwner() == self.playerID():
      if virus.getLevel() != viruso.getLevel():
        print("can't move onto this friendly unit")
        return False
    elif virus.getOwner() != self.playerID() and  virus.getLevel() >= viruso.getLevel():
     if abs(virus.getX() - viruso.getX()) + abs(virus.getY() - viruso.getY()) == 2:
       print("enemy will kill you")
       return False
         
   print("leaving check")
   return True
          
 def circle(self,virus, base):
    print("calling circle XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX")
    if abs(base.getX()-virus.getX()) + abs(base.getY()-virus.getY()) > 1:
  
     if base.getX()>virus.getX():
      if self.check(virus,virus.getX()+1,virus.getY()):
       virus.move(virus.getX()+1,virus.getY())
    
     if base.getX() < virus.getX():
      if self.check(virus,virus.getX()-1,virus.getY()):
       virus.move(virus.getX()-1,virus.getY())
    
     if base.getX() == virus.getX():
    
      if base.getY()+1 > virus.getY():
       if self.check(virus,virus.getX(),virus.getY()+1):
        virus.move(virus.getX(),virus.getY()+1)
    
      if base.getY()+1 < virus.getY():
       if self.check(virus,virus.getX(),virus.getY()-1):
        virus.move(virus.getX(),virus.getY()-1)
            
    if path.count == 1:
     if path.direction1 == 1:
      path.direction1 = 0
      self.reverse(virus,base)
     elif path.count == 2:
      if path.directon2 == 1:
       path.direction2 = 0
       self.reverse(virus,base)
     elif path.count == 3:
      if path.direction3 == 1:
       path.direction3 = 0
       self.reverse(virus,base)
                                                                                                
    
    elif virus.getX() == base.getX() and virus.getY() == base.getY()+1:
     if self.check(virus, base.getX()+1, base.getY()+1):
      virus.move(virus.getX()+1,virus.getY())
     else:
       print("Did you make it this far?")
       if path.count == 1:
        if path.direction1 == 1:
         path.direction1 = 0
         self.reverse(virus,base)
       elif path.count == 2:  
        if path.directon2 == 1:
         path.direction2 = 0
         self.reverse(virus,base)
       elif path.count == 3:
        if path.direction3 == 1:
         path.direction3 = 0
         self.reverse(virus,base)
                      
    elif virus.getX() == base.getX()+1 and virus.getY() == base.getY()+1:
     if self.check(virus, base.getX()+1, base.getY()):
      virus.move(virus.getX(),virus.getY()-1)
    
    elif virus.getX() == base.getX()+1 and virus.getY() == base.getY():
     if self.check(virus,base.getX()+1,base.getY()-1):
      virus.move(virus.getX(),virus.getY()-1)
    
    elif virus.getX() == base.getX()+1 and virus.getY() == base.getY()-1:
     if self.check(virus,base.getX(),base.getY()-1):
      virus.move(virus.getX()-1,virus.getY())
    
    elif virus.getX() == base.getX() and virus.getY() == base.getY()-1:
     if self.check(virus,base.getX()-1,base.getY()-1):
      virus.move(virus.getX()-1,virus.getY())
      
    elif virus.getX() == base.getX()-1 and virus.getY() == base.getY()-1:
     if self.check(virus,base.getX()-1,base.getY()):
      virus.move(virus.getX(),virus.getY()+1)
    
    elif virus.getX() == base.getX()-1 and virus.getY() == base.getY():
     if self.check(virus,base.getX()-1,base.get()+1):
      virus.move(virus.getX(),virus.getY()+1)
    
    elif virus.getX() == base.getX()-1 and virus.getX()== base.getY()+1:
     if self.check(virus,base.getX()+1,base.getY()):
      virus.move(virus.getX()+1,virus.getY())
    
    path.count+=1
    path.count%=3
    print("leaving circle")
    
 def reverse(self,virus,base):                                                                                    
   print("calling reverse OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO")
   if virus.getX() == base.getX() and virus.getY() == base.getY()+1:
    if self.check(virus, base.getX()-1, base.getY+1()):
     virus.move(virus.getX()-1,virus.getY())
                                                                                       
   elif virus.getX() == base.getX()-1 and virus.getY() == base.getY()+1:
    if self.check(virus, base.getX()-1, base.getY()):
     virus.move(virus.getX(),virus.getY()-1)
                                                                                                            
   elif virus.getX() == base.getX()-1 and virus.getY() == base.getY():
    if self.check(virus,base.getX()-1,base.getY()-1):
     virus.move(virus.getX()-1,virus.getY()-1)
                                                                                                                                                            
   elif virus.getX() == base.getX()-1 and virus.getY() == base.getY()-1:
    if self.check(virus,base.getX(),base.getY()-1):
     virus.move(virus.getX()+1,virus.getY())
                                                                                                                                                                       
   elif virus.getX() == base.getX() and virus.getY() == base.getY()-1:
    if self.check(virus,base.getX()+1,base.getY()-1):
     virus.move(virus.getX()+1,virus.getY())
                                                                                                                                                                                         
   elif virus.getX() == base.getX()+1 and virus.get() == base.getY()-1:
    if self.check(virus,base.getX()+1,base.getY()):
     virus.move(virus.getX(),virus.getY()+1)
                                                                                                                                                                                      
   elif virus.getX() == base.getX()+1 and virus.getY() == base.getY():
    if self.check(virus,base.getX()+1,base.get()+1):
     virus.move(virus.getX(),virus.getY()+1)
    else:
     print("Wow, you made it all the way here!")
     if path.count == 1: 
      if path.direction1 == False:
       path.direction1 = True
       if self.check(virus,base.getX()+1,base.getY()-1):
         virus.move(virus.getX(),virust.getY()-1)
       else:
        virus.move(virus.getX()+1,virus.getY())
     elif path.count == 2:
      if path.direction2 == False:
       path.direction2 = True
       if self.check(virus,base.getX()+1,base.getY()-1):
        virus.move(virus.getX(),virust.getY()-1)
       else:
        virus.move(virus.getX()+1,virus.getY())
     elif path.count == 3:
      if path.direction3 == False:
       path.direction3 = True
       if self.check(virus,base.getX()+1,base.getY()-1):
        virus.move(virus.getX(),virust.getY()-1)
       else:
        virus.move(virus.getX()+1,virus.getY())
                                                    
   elif virus.getX() == base.getX()+1 and virus.getX()== base.getY()+1:
    if self.check(virus,base.getX()-1,base.getY()):
     virus.move(virus.getX()-1,virus.getY())
  
   path.count+=1
   path.count%=3                                                                                                                                                                                                                                 
   print("leaving reverse")

 def cost(self,level):
   return int(10*1.8**level)
 
           
 def run(self):
 
   sealife = []
   for fish in self.viruses:
     print("GFLDFKDS")
     if fish.getOwner() == self.playerID():
      sealife.append(fish)  
      print("UNDER DA SEA")
 
   aqua = waters()
   
   print("calling run---------------------------------")
   toplevel = 1
   for rival in self.viruses:
    if rival.getOwner() != self.playerID():
     if rival.getLevel() > toplevel:
       toplevel = rival.getLevel()+1

   for base in self.bases:
    if base.getOwner() == self.playerID() and base.getSpawnsLeft() == 1:
     print("1")
     if len(sealife) < 4:
      base.spawn(toplevel)
     for fish in self.viruses: 
       if not (fish.getX() == base.getX() and fish.getY() == base.getY()):
      # for player in self.players:
      #  if player.getId() == self.playerID() and player.getByteDollars() >= self.cost(shark.getLevel()):
         print("2")
         if aqua.checkwater(toplevel) == 1:
           print("shark")
           shark = base.spawn(toplevel)
           sealife.append(shark)
      #  elif player.getId() == self.playerID() and player.getByteDollars() >= self.cost(0):
         else:    
          print("spawning shrimp")
          shrimp = base.spawn(0)
          sealife.append(shrimp)

   for fish in self.viruses:
    print("3")
    if fish.getOwner() == self.playerID() and fish.getLevel < toplevel:#and virus.getMovesLeft == 1 and virus.getLiving == 1:
     print("fish level",fish.level,"toplevel",toplevel)
     for tile in self.tiles:
      if tile.getOwner() != fish.playerID():
       if tile.getX() > fish.getX():
        if self.check(fish,fish.getX()+1,fish.getY()):
         fish.move(fish.getX()+1,fish.getY())
         sealife.remove(fish)

       elif tile.getX() < fish.getX():
        if self.check(fish,fish.getX()-1,fish.getY()):
         fish.move(fish.getX()-1,fish.getY())
         sealife.remove(fish)

       elif tile.getX() == fish.getX():
        if tile.getY() > fish.getY():
         if self.check(fish,fish.getX(),fish.getY()+1):
          fish.move(fish.getX(), fish.getY()+1)
          sealife.remove(fish)
       
        elif tile.getY() < fish.getY():
         if self.check(fish,fish.getX(),fish.getY()-1):
          fish.move(fish.getX(),fish.getY()-1)
          sealife.remove(fish)
	  
   for shark in self.viruses:
    print("4")
    if shark.getOwner() == self.playerID():# and shark.getMovesLeft == 1 and shark.getLiving == 1:
     print("a")
     for base in self.bases:
       print("c")
       if base.getOwner() != self.playerID(): 
        if path.count == 0:
         self.circle(shark,base)
        elif path.count == 1:
         self.circle(shark,base)
        elif path.count == 2:
         self.circle(shark,base)  

  # for virus in self.viruses:
  #  if virus.level <= toplevel:
  #   fishing = 0
  #
  #   if waters.count = 0:
  #    waters.shark1 = 1
  #   elif waters.count = 1:
  #    waters.shark2 = 1
  #   elif waters.count3 = 2

   print("5")
   return 1
   


 def __init__(self, conn):
    print("ARE YOU DOING THIS?!")
    BaseAI.__init__(self, conn)  

