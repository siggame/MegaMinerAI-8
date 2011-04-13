import com.sun.jna.Pointer;

///Generic Unit
abstract class Unit extends Mappable 
{
  public Unit(Pointer p)
  {
    super(p);
  }
  abstract boolean validify();
    
    //commands
    
  ///Move the unit to the designated X and Y coordinates
  int move(int x, int y)
  {
    validify();
    return Client.INSTANCE.unitMove(ptr, x, y);
  }
  ///Allows a unit to display a message to the screen.
  int talk(String message)
  {
    validify();
    return Client.INSTANCE.unitTalk(ptr, message);
  }
  ///Attempt to attack the given unit
  int attack(Unit Target)
  {
    validify();
    Target.validify();
    return Client.INSTANCE.unitAttack(ptr, Target.ptr);
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
  ///Health of the unit
  public int getHealth()
  {
    validify();
    return Client.INSTANCE.unitGetHealth(ptr);
  }
  ///Attacking strength of the unit
  public int getStrength()
  {
    validify();
    return Client.INSTANCE.unitGetStrength(ptr);
  }
  ///Displays the remaining moves for this unit this turn
  public int getMovesLeft()
  {
    validify();
    return Client.INSTANCE.unitGetMovesLeft(ptr);
  }
  ///Displays the remaining attacks for this unit this turn
  public int getAttacksLeft()
  {
    validify();
    return Client.INSTANCE.unitGetAttacksLeft(ptr);
  }

}
