using System;
using System.Runtime.InteropServices;


///A generic pirate
public class Pirate: Unit 
{
  public IntPtr ptr;
  int ID;
  int iteration;
  public Pirate(IntPtr p)
  {
    ptr = p;
    ID = Client.pirateGetId(ptr);
    iteration = BaseAI.iteration;
  }

public override bool validify()
  {
    if(iteration == BaseAI.iteration) return true;
    for(int i = 0; i < BaseAI.pirates.Length; i++)
    {
      if(BaseAI.pirates[i].ID == ID)
      {
        ptr = BaseAI.pirates[i].ptr;
        iteration = BaseAI.iteration;
        return true;
      }
    }
    throw new ExistentialError();
  }
    
    //commands
    
  ///Move the unit to the designated X and Y coordinates
  int move(int x, int y)
  {
    validify();
    return Client.pirateMove(ptr, x, y);
  }
  ///Allows a unit to display a message to the screen.
  int talk(string message)
  {
    validify();
    return Client.pirateTalk(ptr, message);
  }
  ///Allows the pirate to pickup treasure on the ground.
  int pickupTreasure(int amount)
  {
    validify();
    return Client.piratePickupTreasure(ptr, amount);
  }
  ///Allows the pirate to drop treasure on the groud.
  int dropTreasure(int amount)
  {
    validify();
    return Client.pirateDropTreasure(ptr, amount);
  }
  ///Pirate builds a port on a land tile with water tile adjacent
  int buildPort()
  {
    validify();
    return Client.pirateBuildPort(ptr);
  }
  ///Attempt to attack the given unit
  int attack(Unit Target)
  {
    validify();
    Target.validify();
    return Client.pirateAttack(ptr, Target.ptr);
  }
    
    //getters
    
  ///Unique Identifier
  public int getId()
  {
    validify();
    return Client.pirateGetId(ptr);
  }
  ///The X position of this object.  X is horizontal, with 0,0 as the top left corner
  public int getX()
  {
    validify();
    return Client.pirateGetX(ptr);
  }
  ///The Y position of this object.  Y is vertical, with 0,0 as the top left corner
  public int getY()
  {
    validify();
    return Client.pirateGetY(ptr);
  }
  ///The owner of the unit
  public int getOwner()
  {
    validify();
    return Client.pirateGetOwner(ptr);
  }
  ///health of the unit
  public int getHealth()
  {
    validify();
    return Client.pirateGetHealth(ptr);
  }
  ///attacking strength of the unit
  public int getStrength()
  {
    validify();
    return Client.pirateGetStrength(ptr);
  }
  ///checks if the unit has moved this turn
  public int getHasMoved()
  {
    validify();
    return Client.pirateGetHasMoved(ptr);
  }
  ///checks if the unit has moved this turn
  public int getHasAttacked()
  {
    validify();
    return Client.pirateGetHasAttacked(ptr);
  }

}
