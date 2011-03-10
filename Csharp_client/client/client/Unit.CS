using System;
using System.Runtime.InteropServices;


///Generic Unit
abstract class Unit: Mappable 
{
  IntPtr ptr;
  int ID;
  int iteration;
  public Unit(IntPtr p)
  {
    ptr = p;
    ID = Client.INSTANCE.unitGetId(ptr);
    iteration = BaseAI.iteration;
  }

  abstract bool validify();
    
    //commands
    
  ///Move the unit to the designated X and Y coordinates
  int move(int x, int y)
  {
    validify();
    return Client.INSTANCE.unitMove(ptr, x, y);
  }
  ///Allows a unit to display a message to the screen.
  int talk(string message)
  {
    validify();
    return Client.INSTANCE.unitTalk(ptr, message);
  }
    
    //getters
    
  ///Unique Identifier
  public int getId()
  {
    validify();
    return Client.INSTANCE.unitGetId(ptr);
  }
  ///The X position of this object.  X is horizontal, with 0,0 as the top left corner
  public int getX()
  {
    validify();
    return Client.INSTANCE.unitGetX(ptr);
  }
  ///The Y position of this object.  Y is vertical, with 0,0 as the top left corner
  public int getY()
  {
    validify();
    return Client.INSTANCE.unitGetY(ptr);
  }
  ///The owner of the unit
  public int getOwner()
  {
    validify();
    return Client.INSTANCE.unitGetOwner(ptr);
  }
  ///health of the unit
  public int getHealth()
  {
    validify();
    return Client.INSTANCE.unitGetHealth(ptr);
  }
  ///attacking strength of the unit
  public int getStrength()
  {
    validify();
    return Client.INSTANCE.unitGetStrength(ptr);
  }

}
