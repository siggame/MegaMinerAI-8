import com.sun.jna.Pointer;

///A treasure
class Treasure extends Mappable 
{
  public Treasure(Pointer p)
  {
    super(p);
  }
  boolean validify()
  {
    if(iteration == BaseAI.iteration) return true;
    for(int i = 0; i < BaseAI.treasures.length; i++)
    {
      if(BaseAI.treasures[i].ID == ID)
      {
        ptr = BaseAI.treasures[i].ptr;
        iteration = BaseAI.iteration;
        return true;
      }
    }
    throw new ExistentialError();
  }
    
    //commands
    
    
    //getters
    
  ///Unique Identifier
  public int getId()
  {
    validify();
    return Client.INSTANCE.treasureGetId(ptr);
  }
  ///The X position of this object.  X is horizontal, with 0,0 as the top left corner
  public int getX()
  {
    validify();
    return Client.INSTANCE.treasureGetX(ptr);
  }
  ///The Y position of this object.  Y is vertical, with 0,0 as the top left corner
  public int getY()
  {
    validify();
    return Client.INSTANCE.treasureGetY(ptr);
  }
  ///The ID of the pirate carrying this treasure, 0 if not carried
  public int getPirateID()
  {
    validify();
    return Client.INSTANCE.treasureGetPirateID(ptr);
  }
  ///The amount of gold in this treaure
  public int getAmount()
  {
    validify();
    return Client.INSTANCE.treasureGetAmount(ptr);
  }

}
