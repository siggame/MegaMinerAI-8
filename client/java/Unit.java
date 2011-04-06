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
  ///checks if the unit has moved this turn
  public int getHasMoved()
  {
    validify();
    return Client.INSTANCE.unitGetHasMoved(ptr);
  }
  ///checks if the unit has moved this turn
  public int getHasAttacked()
  {
    validify();
    return Client.INSTANCE.unitGetHasAttacked(ptr);
  }

}
