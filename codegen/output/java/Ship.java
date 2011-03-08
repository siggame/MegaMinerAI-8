import com.sun.jna.Pointer;

///A generic ship
class Ship: extends Unit 
{
  Pointer ptr;
  int ID;
  int iteration;
  public Ship(Pointer p)
  {
    ptr = p;
    ID = Client.INSTANCE.shipGetId(ptr);
    iteration = BaseAI.iteration;
  }

  boolean validify()
  {
    if(iteration == BaseAI.iteration) return true;
    for(int i = 0; i < BaseAI.ships.length; i++)
    {
      if(BaseAI.ships[i].ID == ID)
      {
        ptr = BaseAI.ships[i].ptr;
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
    return Client.INSTANCE.shipMove(ptr, x, y);
  }
  ///Allows a unit to display a message to the screen.
  int talk(String message)
  {
    validify();
    return Client.INSTANCE.shipTalk(ptr, message);
  }
  ///Attempt to attack the given unit
  int attack(Unit Target)
  {
    validify();
    Target.validify();
    return Client.INSTANCE.shipAttack(ptr, Target.ptr);
  }
    
    //getters
    
  ///Unique Identifier
  public int getId()
  {
    validify();
    return Client.INSTANCE.shipGetId(ptr);
  }
  ///The X position of the top left corner of this object.  X is horizontal
  public int getX()
  {
    validify();
    return Client.INSTANCE.shipGetX(ptr);
  }
  ///The Y position of the top left corner of this object.  Y is vertical
  public int getY()
  {
    validify();
    return Client.INSTANCE.shipGetY(ptr);
  }
  ///The owner of the unit
  public int getOwner()
  {
    validify();
    return Client.INSTANCE.shipGetOwner(ptr);
  }
  ///health of the unit
  public int getHealth()
  {
    validify();
    return Client.INSTANCE.shipGetHealth(ptr);
  }
  ///attacking strength of the unit
  public int getStrength()
  {
    validify();
    return Client.INSTANCE.shipGetStrength(ptr);
  }

}
