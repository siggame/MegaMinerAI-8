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

class AI(BaseAI):
  """The class implementing gameplay logic."""
  @staticmethod
  def username():
    return "Kellogg"

  @staticmethod
  def password():
    return "password"

  def init(self):
    pass

  def end(self):
    pass

  def run(self):
   toplevel = 1
   shark1 = False
   shark2 = False
   shark3 = False
   for rival in self.viruses:
    if rival.getOwner() != self.playerID(): 
     if rival.getLevel() > toplevel:
       toplevel = rival.getLevel()+1
   for base in self.bases:
    if base.getOwner == self.playerID() and base.getSpawnsLeft == 1:
     if shark1 == False:
      base.spawn(toplevel)
      shark = True
     elif shark2 == False:
      base.spawn(toplevel)
      shark = True
     elif shark3 == False:
      base.spawn(toplevel)
      shark = True
     else:
       base.spawn(0)
 
   for shark in self.viruses:
    if shark.getOwner() == self.playerID() and shark.getMovesLeft == 1 and shark.getLiving == 1:
     if shark.getLevel() == toplevel:
      for base in self.bases:
       if self.count == 0:
        circle(shark,base)
       elif self.count == 1:
        circle(shark,base)
       elif self.count == 2:
        circle(shark,base)
    
#     if shark.getOwner() == self.playerID():
#      if shark.getLevel() == toplevel:
#       for rival in self.viruses:
#        if rival.getOwner() != self.playerID(): 
#         if rival.getLevel() == toplevel:
#          if rival.getX() > shark.getX():
#           if check(shark,virus.getX()+1,shark.getY()):
#             shark.move(virus.getX()+1,shark.getY())
#           elif rival.getX() < shark.level:
#            shark.move(shark.getX()-1,shark.getY())
#           else:
#            if rival.getY() > shark.getY():
#             shark.move(getX(),shark.getY()+1)
#            else:
#             shark.move(getX(),shark.getY()-1)
   
   for virus in self.viruses:
    if virus.getOwner() == self.playerID() and virus.getMovesLeft == 1 and virus.getLiving == 1:
     for tile in self.tiles:
      if tile.getOwner() != virus.playerID(): 
       if tile.getX() > virus.getX():
        if check(virus,virus.getX()+1,virus.getY()):
         virus.move(virus.getX()+1,virus.getY())
       
       elif tile.getX() < virus.getX():
        if check(virus,virus.getX()-1,virus.getY()):
         virus.move(virus.getX()-1,virust.getY())
       
       elif tile.getX() == virus.getX():
        if tile.getY() > virus.getY():
         if check(virus,virus.getX(),virus.getY()+1):
          virus.move(virus.getX(), virus.getY()+1)
        
        elif tile.getY() < virus.getY():
         if check(virus,virus.getX(),virus.getY()-1):
          virus. move(virus.getX(),virus.getY()-1)                                               
       
   return 1

  def __init__(self, conn):
      BaseAI.__init__(self, conn)
   
  def check(viruso,x,y):
   if viruso.getID() != self.playerID():
    return False
    
   if abs(viruso.getX()-x) + abs(viruso.getY()-y) !=1:
    return False
    
   for tile in self.tiles:
    if tile.owner == 3 and tile.getX() == x and tile.getY() == y:
      return False
   
   if x<0 or x>40:
    return False
   if y<0 or y>20:
    return False
            
   if viruso.movesLeft != 1:
    return False
   
   for base in self.bases:
    if base.getX() == x and base.getY() == y:
     return False
    
   for virus in self.viruses:
    if virus.getX() == x and virus.getY() == y:
     if virus.getOwner() == self.playerID():
      if virus.getLevel() != viruso.getLevel():
        return False
     elif virus.getOwner() != self.playerID():
      if virus.getLevel() >= viruso.getLevel():
       return False
    
   return True
          
  def circle(virus, base):
    if abs(base.getX()-virus.getX()) + abs(base.getY()-virus.getY()) > 1:
     if base.getX()>virus.getX():
      if check(virus,virus.getX()+1,virus.getY()):
       virus.move(virus.getX()+1,virus.getY())
    
     if base.getX() < virus.getX():
      if check(virus,virus.getX()-1,virus.getY()):
       virus.move(virus.getX()-1,virus.getY())
    
     if base.getX() == virus.getX():
      if base.getY()+1 > virus.getY():
       if check(virus,virus.getX(),virus.getY()+1):
        virus.move(virus.getX(),virus.getY()+1)
      if base.getY()+1<virus.getY():
       if check(virus,virus.getX(),virus.getY()-1):
        virus.move(virus.getX(),virus.getY()-1)
            
    elif virus.getX() == base.getX() and virus.getY() == base.getY()+1:
     if check(virus, base.getX()+1, base.getY+1()):
      virus.move(virus.getX()+1,virus.getY())
     else:
       if path.count == 1:
        if path.direction1 == 1:
         path.direction1 = 0
         reverse(virus,base)
       elif path.count == 2:  
        if path.directon2 == 1:
         path.direction2 = 0
         reverse(virus,base)
       elif path.count == 3:
        if path.direction3 == 1:
         path.direction3 = 0
         reverse(virus,base)
                      
    elif virus.getX() == base.getX()+1 and virus.getY() == base.getY()+1:
     if check(virus, base.getX()+1, base.getY()):
      virus.move(virus.getX(),virus.getY()-1)
    
    elif virus.getX() == base.getX()+1 and virus.getY() == base.getY():
     if check(virus,base.getX()+1,base.getY()-1):
      virus.move(virus.getX(),virus.getY()-1)
    
    elif virus.getX() == base.getX()+1 and virus.getY() == base.getY()-1:
     if check(virus,base.getX(),base.getY()-1):
      virus.move(virus.getX()-1,virus.getY())
    
    elif virus.getX() == base.getX() and virus.getY() == base.getY()-1:
     if check(virus,base.getX()-1,base.getY()-1):
      virus.move(virus.getX()-1,virus.getY())
      
    elif virus.getX() == base.getX()-1 and virus.get() == base.getY()-1:
     if check(virus,base.getX()-1,base.getY()):
      virus.move(virus.getX(),virus.getY()+1)
    
    elif virus.getX() == base.getX()-1 and virus.getY() == base.getY():
     if check(virus,base.getX()-1,base.get()+1):
      virus.move(virus.getX(),virus.getY()+1)
    
    elif virus.getX() == base.getX()-1 and virus.getX()== base.getY()+1:
     if check(virus,base.getX()+1,base.getY()):
      virus.move(virus.getX()+1,virus.getY())
    
    path.count+=1
    path.count%=3

  def reverse(virus,base):                                                                                    
   if virus.getX() == base.getX() and virus.getY() == base.getY()+1:
    if check(virus, base.getX()-1, base.getY+1()):
     virus.move(virus.getX()-1,virus.getY())
                                                                                       
   elif virus.getX() == base.getX()-1() and virus.getY() == base.getY()+1:
    if check(virus, base.getX()-1, base.getY()):
     virus.move(virus.getX(),virus.getY()-1)
                                                                                                            
   elif virus.getX() == base.getX()-1 and virus.getY() == base.getY():
    if check(virus,base.getX()-1,base.getY()-1):
     virus.move(virus.getX()-1,virus.getY()-1)
                                                                                                                                                            
   elif virus.getX() == base.getX()-1 and virus.getY() == base.getY()-1:
    if check(virus,base.getX(),base.getY()-1):
     virus.move(virus.getX()+1,virus.getY())
                                                                                                                                                                       
   elif virus.getX() == base.getX() and virus.getY() == base.getY()-1:
    if check(virus,base.getX()+1,base.getY()-1):
     virus.move(virus.getX()+1,virus.getY())
                                                                                                                                                                                         
   elif virus.getX() == base.getX()+1 and virus.get() == base.getY()-1:
    if check(virus,base.getX()+1,base.getY()):
     virus.move(virus.getX(),virus.getY()+1)
                                                                                                                                                                                      
   elif virus.getX() == base.getX()+1 and virus.getY() == base.getY():
    if check(virus,base.getX()+1,base.get()+1):
     virus.move(virus.getX(),virus.getY()+1)
    else:
     if path.count == 1: 
      if path.direction1 == False:
       path.direction1 = True
       if check(virus,base.getX()+1,base.getY()-1):
         virus.move(virus.getX(),virust.getY()-1)
       else:
        virus.move(virus.getX()+1,virus.getY())
     elif path.count == 2:
      if path.direction2 == False:
       path.direction2 = True
       if check(virus,base.getX()+1,base.getY()-1):
        virus.move(virus.getX(),virust.getY()-1)
       else:
        virus.move(virus.getX()+1,virus.getY())
     elif path.count == 3:
      if path.direction3 == False:
       path.direction3 = True
       if check(virus,base.getX()+1,base.getY()-1):
        virus.move(virus.getX(),virust.getY()-1)
       else:
        virus.move(virus.getX()+1,virus.getY())
                                                    
   elif virus.getX() == base.getX()+1 and virus.getX()== base.getY()+1:
    if check(virus,base.getX()-1,base.getY()):
     virus.move(virus.getX()-1,virus.getY())
  
   path.count+=1
   path.count%=3                                                                                                                                                                                                                                 
