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
#  print("shark in the water, our shark")
  for shark in AI.viruses:
   if shark.getLevel() == toplevel:
    self.shiver += 1
  if self.shiver <= 3:
   return True 
  
 def bloodInTheWater(self,shark,ID,prey,shiver): 
  min_dis = 1000  
  for base in prey:
   print(base.getX())
   for predator in shiver: 
    if abs(base.getX()-shark.getX()) + abs(base.getY()-shark.getY()) < abs(base.getX()-predator.getX()) + abs(predator.getY()-predator.getY()):
     #if abs(base.getX()-shark.getX()) + abs(base.getY()-shark.getY()) < min_dis:
      min_dis = abs(base.getX()-shark.getX()) + abs(base.getY()-shark.getY())
      return base
    elif abs(base.getX()-shark.getX()) + abs(base.getY()-shark.getY()) < min_dis:
     min_dis = abs(base.getX()-shark.getX()) + abs(base.getY()-shark.getY())         
     return base
    else:
     return base
      
 def planktonHunt(self,shrimp,ID,open_water):
   min_dis = 10000
   for tile in open_water:
     if tile.getOwner() != ID and abs(tile.getX()-shrimp.getX()) + abs(tile.getY()-shrimp.getY()) < min_dis:
      food = tile
      min_dis = abs(tile.getX()-shrimp.getX()) + abs(tile.getY()-shrimp.getY())
   return food     
  
class AI(BaseAI):
 
 toplevel = 100
 
 """The class implementing gameplay logic."""
 @staticmethod
 def username():
    return "Applejack"
         
 @staticmethod
 def password():
   return "password"
                  
 def init(self):
    pass
                        
 def end(self):
    pass

 
 def check(self,viruso,x,y):
   if viruso.getOwner() != self.playerID():
    return False
    
   if abs(viruso.getX()-x) + abs(viruso.getY()-y) >1:
    return False
    
   for tile in self.tiles:
    if tile.getX() == x and tile.getY() == y and tile.getOwner == 3:
      return False
   
   if x<0 or x>40:
    return False
   elif y<0 or y>20:
    return False
            
   if viruso.getMovesLeft == 0:
    return False
   
   for base in self.bases:
    if base.getX() == x and base.getY() == y:
     return False
    
   if viruso.getLevel < self.toplevel:
    for virus in self.viruses:
     if virus.getOwner() == self.PlayerID() and virus.getLevel == toplevel:
      if abs(virus.getX() - viruso.getX()) + abs(virus.getY() - viruso.getY()) == 2:
       return False          

   for virus in self.viruses:
    if virus.getX() == x and virus.getY() == y:
     if virus.getOwner() == self.playerID():
      if virus.getLevel() != viruso.getLevel():
        return False
    elif virus.getOwner() != self.playerID() and  virus.getLevel() >= viruso.getLevel():
     if abs(virus.getX() - viruso.getX()) + abs(virus.getY() - viruso.getY()) == 2:
       return False
         
   return True
          
 def circle(self,virus, base):
   if abs(base.getX()-virus.getX()) + abs(base.getY()-virus.getY()) > 1:
  
    if base.getX()>virus.getX():
     if self.check(virus,virus.getX()+1,virus.getY()):
      virus.move(virus.getX()+1,virus.getY())
     elif self.check(virus,virus.getX(),virus.getY()+1): 
      virus.move(virus.getX(),virus.getY()+1)
     elif self.check(virus,virus.getX(),virus.getY()-1):
      virus.move(virus.getX(),virus.getY()-1)
	  
    if base.getX() < virus.getX():
     if self.check(virus,virus.getX()-1,virus.getY()):
      virus.move(virus.getX()-1,virus.getY())
     elif self.check(virus,virus.getX(),virus.getY()+1): 
      virus.move(virus.getX(),virus.getY()+1)
     elif self.check(virus,virus.getX(),virus.getY()-1):
      virus.move(virus.getX(),virus.getY()-1)
	
    if base.getX() == virus.getX():
    #if base.getY()+1 > virus.getY():
     if self.check(virus,virus.getX(),virus.getY()+1):
      virus.move(virus.getX(),virus.getY()+1)
     elif self.check(virus,virus.getX+1(),virus.getY()): 
      virus.move(virus.getX()+1,virus.getY())
     elif self.check(virus,virus.getX()-1,virus.getY()):
      virus.move(virus.getX()-1,virus.getY())
       
    if base.getY()+1 < virus.getY():
     if self.check(virus,virus.getX(),virus.getY()-1):
      virus.move(virus.getX(),virus.getY()-1)
     elif self.check(virus,virus.getX(),virus.getY()+1): 
      virus.move(virus.getX(),virus.getY()+1)
     elif self.check(virus,virus.getX(),virus.getY()-1):
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
       if path.count == 1:
        if path.direction1 == 1:
         path.direction1 = 0
         self.reverse(virus,base)
       elif path.count == 2:  
        if path.direction2 == 1:
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
     if self.check(virus,base.getX()-1,base.getX()+1):
      virus.move(virus.getX(),virus.getY()+1)
    
    elif virus.getX() == base.getX()-1 and virus.getX()== base.getY()+1:
     if self.check(virus,base.getX()+1,base.getY()):
      virus.move(virus.getX()+1,virus.getY())
    
    path.count+=1
    path.count%=3
 #   print("leaving circle")"""
    
 def reverse(self,virus,base):                                                                                    
 #  print("calling reverse OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO")
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
 #    print("Wow, you made it all the way here!")
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
 #  print("leaving reverse")

 def cost(self,level):
   return int(10*1.8**level)
 
           
    
 def  open_water(self):
   open_water = set()
   for tile in self.tiles:
    if tile.getOwner() != self.playerID() and tile.getOwner() != 3:
     for base in AI.bases:
      if tile.getX() != base.getX() and tile.getY() != base.getY():
       open_water.add(tile)
   return open_water 

 def  sealife(self): 
   sealife = set()
   for fish in self.viruses:
     if fish.getOwner() == self.playerID():
      sealife.add(fish)
   return sealife  
 
 def  prey(self):
   prey = set()
   for base in self.bases:
    if base.getOwner() == self.playerID():
     prey.add(base)
   return prey
   
 def  sharks(self):
    shiver = set()
    for virus in self.viruses:
     if virus.getLevel() == self.toplevel:
      shiver.add(virus)
    return shiver
   
 def updateSharks(self,shiver):
     for shark in shiver:
      if shark.getLevel() < self.toplevel:
       self.shiver.remove(shark)
             
 def run(self):     
   aqua = waters()
   
 #  print("calling run---------------------------------")
   toplevel = 1    
   for rival in self.viruses:
    if rival.getOwner() != self.playerID():
     if rival.getLevel() > toplevel:
       toplevel = rival.getLevel()+1

   for player in self.players:
    if player.getId() == self.playerID():         
      self.updateSharks(self.sharks())
      for base in self.bases:
      # print("going through bases",self.turnNumber())
       if base.getOwner() == self.playerID() and base.getSpawnsLeft() >0:
         sharks = self.sharks()
         if len(sharks)< 4 and player.getByteDollars() >= self.cost(toplevel):
          base.spawn(toplevel)
         else:
       #for fish in self.viruses: 
        #if not (fish.getX() == base.getX() and fish.getY() == base.getY()):
      #   for player in self.players:
          #if player.getId() == self.playerID() and player.getByteDollars() >= self.cost(toplevel):
         #  if aqua.checkwater(toplevel) == 1:
 #           print("shark")
       #     shark = base.spawn(toplevel)
        # sealife.append(shark)
          if player.getId() == self.playerID():# and player.getByteDollars() >= self.cost(0):
 #         print("spawning shrimp")
           shrimp = base.spawn(0)
           self.sealife().add(shrimp)
        
   seaLife = self.sealife()
   Sharks =self.sharks()
   school = seaLife - Sharks
   for fish in school:
   # if fish.getOwner() == self.playerID() and fish.getLevel() < toplevel:#and virus.getMovesLeft == 1 and virus.getLiving == 1:
 #    print("fish level",fish.getLevel(),"toplevel",toplevel)
     #for tile in self.tiles:
       tile = aqua.planktonHunt(fish,self.playerID(),self.open_water())      
       if tile.getX() > fish.getX():
        if self.check(fish,fish.getX()+1,fish.getY()):
         fish.move(fish.getX()+1,fish.getY())
        # sealife.remove(fish)
         self.open_water().discard(tile)
         
        elif self.check(fish,fish.getX(),fish.getY()+1):
         fish.move(fish.getX(),fish.getY()+1)
        #  sealife.remove(fish)
         self.open_water().discard(tile)

        elif self.check(fish,fish.getX(),fish.getY()-1):
         fish.move(fish.getX(),fish.getY()-1)
       #  sealife.remove(fish)
         self.open_water().discard(tile)                                     

       elif tile.getX() < fish.getX():
        if self.check(fish,fish.getX()-1,fish.getY()):
         fish.move(fish.getX()-1,fish.getY())
       #  sealife.remove(fish)
         self.open_water().discard(tile)

	elif self.check(fish,fish.getX(),fish.getY()+1):
          fish.move(fish.getX(),fish.getY()+1)
#          sealife.remove(fish)
          self.open_water().discard(tile)

        elif self.check(fish,fish.getX(),fish.getY()-1):
          fish.move(fish.getX(),fish.getY()-1)
 #         sealife.remove(fish)
          self.open_water().discard(tile)
          
       elif tile.getX() == fish.getX():
        if tile.getY() > fish.getY():
         if self.check(fish,fish.getX(),fish.getY()+1):
          fish.move(fish.getX(), fish.getY()+1)
  #        sealife.remove(fish)
          self.open_water().discard(tile)
         
         elif self.check(fish,fish.getX()-1,fish.getY()):
          fish.move(fish.getX()-1, fish.getY())
   #       sealife.remove(fish)
          self.open_water().discard(tile)                            
         
         elif self.check(fish,fish.getX()+1,fish.getY()):
          fish.move(fish.getX()+1, fish.getY())
   #       sealife.remove(fish)
          self.open_water().discard(tile)                           
         
        elif tile.getY() < fish.getY():
         if self.check(fish,fish.getX(),fish.getY()-1):
          fish.move(fish.getX(),fish.getY()-1)
    #      sealife.remove(fish)
	  self.open_water().discard(tile)
	
	 elif self.check(fish,fish.getX()+1,fish.getY()):
	  fish.move(fish.getX()+1, fish.getY())
#	  sealife.remove(fish)
	  self.open_water().discard(tile)
	  
         elif self.check(fish,fish.getX()-1,fish.getY()):
          fish.move(fish.getX()-1, fish.getY())
 #         sealife.remove(fish)
          self.open_water().discard(tile)                                        	                                             	
	
	  
   for shark in self.sharks():
 #   print("4")
   # if shark.getOwner() == self.playerID():# and shark.getMovesLeft == 1 and shark.getLiving == 1:
 #      print("a")
       base = aqua.bloodInTheWater(shark,self.playerID(),self.prey(),self.sharks())      
 #      print("c")
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

 #  print("5")
   return 1
   


 def __init__(self, conn):
    BaseAI.__init__(self, conn)  

