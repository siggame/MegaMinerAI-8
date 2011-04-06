using System;
using System.Runtime.InteropServices;


///A generic pirate
public class Pirate: Unit 
{
  
  public Pirate()
  {
  }
  
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
  public new int move(int x, int y)
  {
    validify();
    return Client.pirateMove(ptr, x, y);
  }
  ///Allows a unit to display a message to the screen.
  public new int talk(string message)
  {
    validify();
    return Client.pirateTalk(ptr, message);
  }
  ///Attempt to attack the given unit
  public new int attack(Unit Target)
  {
    validify();
    Target.validify();
    return Client.pirateAttack(ptr, Target.ptr);
  }
  ///Allows the pirate to pickup treasure on the ground.
  public int pickupTreasure(int amount)
  {
    validify();
    return Client.piratePickupTreasure(ptr, amount);
  }
  ///Allows the pirate to drop treasure on the groud.
  public int dropTreasure(int amount)
  {
    validify();
    return Client.pirateDropTreasure(ptr, amount);
  }
  ///Pirate builds a port on a land tile with water tile adjacent
  public int buildPort()
  {
    validify();
    return Client.pirateBuildPort(ptr);
  }
    
    //getters
    
  ///Unique Identifier
  public new int getId()
  {
    validify();
    return Client.pirateGetId(ptr);
  }
  ///The X position of this object.  X is horizontal, with 0,0 as the top left corner
  public new int getX()
  {
    validify();
    return Client.pirateGetX(ptr);
  }
  ///The Y position of this object.  Y is vertical, with 0,0 as the top left corner
  public new int getY()
  {
    validify();
    return Client.pirateGetY(ptr);
  }
  ///The owner of the unit
  public new int getOwner()
  {
    validify();
    return Client.pirateGetOwner(ptr);
  }
  ///health of the unit
  public new int getHealth()
  {
    validify();
    return Client.pirateGetHealth(ptr);
  }
  ///attacking strength of the unit
  public new int getStrength()
  {
    validify();
    return Client.pirateGetStrength(ptr);
  }
  ///checks if the unit has moved this turn
  public new int getHasMoved()
  {
    validify();
    return Client.pirateGetHasMoved(ptr);
  }
  ///checks if the unit has moved this turn
  public new int getHasAttacked()
  {
    validify();
    return Client.pirateGetHasAttacked(ptr);
  }

}
