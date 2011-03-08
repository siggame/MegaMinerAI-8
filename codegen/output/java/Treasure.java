import com.sun.jna.Pointer;

///A treasure
class Treasure: extends Mappable 
{
  Pointer ptr;
  int ID;
  int iteration;
  public Treasure(Pointer p)
  {
    ptr = p;
    ID = Client.INSTANCE.treasureGetId(ptr);
    iteration = BaseAI.iteration;
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
  ///The X position of the top left corner of this object.  X is horizontal
  public int getX()
  {
    validify();
    return Client.INSTANCE.treasureGetX(ptr);
  }
  ///The Y position of the top left corner of this object.  Y is vertical
  public int getY()
  {
    validify();
    return Client.INSTANCE.treasureGetY(ptr);
  }
  ///The pirate carrying this treasure
  public Pointer getPirate()
  {
    validify();
    return Client.INSTANCE.treasureGetPirate(ptr);
  }

}
