using System;
using System.Runtime.InteropServices;


///Generic Unit
public abstract class Unit: Mappable 
{
  public IntPtr ptr;
  int ID;
  int iteration;
  public Unit(IntPtr p)
  {
    ptr = p;
    ID = Client.unitGetId(ptr);
    iteration = BaseAI.iteration;
  }

public abstract override bool validify();
    
    //commands
    
  ///Move the unit to the designated X and Y coordinates
  int move(int x, int y)
  {
    validify();
    return Client.unitMove(ptr, x, y);
  }
  ///Allows a unit to display a message to the screen.
  int talk(string message)
  {
    validify();
    return Client.unitTalk(ptr, message);
  }
    
    //getters
    
  ///Unique Identifier
  public int getId()
  {
    validify();
    return Client.unitGetId(ptr);
  }
  ///The X position of this object.  X is horizontal, with 0,0 as the top left corner
  public int getX()
  {
    validify();
    return Client.unitGetX(ptr);
  }
  ///The Y position of this object.  Y is vertical, with 0,0 as the top left corner
  public int getY()
  {
    validify();
    return Client.unitGetY(ptr);
  }
  ///The owner of the unit
  public int getOwner()
  {
    validify();
    return Client.unitGetOwner(ptr);
  }
  ///health of the unit
  public int getHealth()
  {
    validify();
    return Client.unitGetHealth(ptr);
  }
  ///attacking strength of the unit
  public int getStrength()
  {
    validify();
    return Client.unitGetStrength(ptr);
  }
  ///checks if the unit has moved this turn
  public int getHasMoved()
  {
    validify();
    return Client.unitGetHasMoved(ptr);
  }
  ///checks if the unit has moved this turn
  public int getHasAttacked()
  {
    validify();
    return Client.unitGetHasAttacked(ptr);
  }

}
