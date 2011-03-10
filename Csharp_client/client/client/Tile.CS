using System;
using System.Runtime.InteropServices;


///A basic tile
class Tile: Mappable 
{
  IntPtr ptr;
  int ID;
  int iteration;
  public Tile(IntPtr p)
  {
    ptr = p;
    ID = Client.INSTANCE.tileGetId(ptr);
    iteration = BaseAI.iteration;
  }

  bool validify()
  {
    if(iteration == BaseAI.iteration) return true;
    for(int i = 0; i < BaseAI.tiles.length; i++)
    {
      if(BaseAI.tiles[i].ID == ID)
      {
        ptr = BaseAI.tiles[i].ptr;
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
    return Client.INSTANCE.tileGetId(ptr);
  }
  ///The X position of this object.  X is horizontal, with 0,0 as the top left corner
  public int getX()
  {
    validify();
    return Client.INSTANCE.tileGetX(ptr);
  }
  ///The Y position of this object.  Y is vertical, with 0,0 as the top left corner
  public int getY()
  {
    validify();
    return Client.INSTANCE.tileGetY(ptr);
  }
  ///land = 0, water = 1
  public int getType()
  {
    validify();
    return Client.INSTANCE.tileGetType(ptr);
  }

}
