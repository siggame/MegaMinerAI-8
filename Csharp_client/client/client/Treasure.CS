using System;
using System.Runtime.InteropServices;


///A treasure
class Treasure: Mappable 
{
  IntPtr ptr;
  int ID;
  int iteration;
  public Treasure(IntPtr p)
  {
    ptr = p;
    ID = Client.INSTANCE.treasureGetId(ptr);
    iteration = BaseAI.iteration;
  }

  bool validify()
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
  ///The pirate carrying this treasure
  public IntPtr getPirate()
  {
    validify();
    return Client.INSTANCE.treasureGetPirate(ptr);
  }

}
