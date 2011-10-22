using System;
using System.Runtime.InteropServices;


///Represents a single space on the map, can be owned by either player, neither player, or be a wall
public class Tile: Mappable 
{
  
  public Tile()
  {
  }
  
  public Tile(IntPtr p)
  {
    ptr = p;
    ID = Client.tileGetId(ptr);
    iteration = BaseAI.iteration;
  }

  public override bool validify()
  {
    if(iteration == BaseAI.iteration) return true;
    for(int i = 0; i < BaseAI.tiles.Length; i++)
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
  public new int getId()
  {
    validify();
    return Client.tileGetId(ptr);
  }
  ///The x coordinate
  public new int getX()
  {
    validify();
    return Client.tileGetX(ptr);
  }
  ///The y cooridnate
  public new int getY()
  {
    validify();
    return Client.tileGetY(ptr);
  }
  ///who owns this tile: 0-First Player, 1-Second Player, 2-Not Owned, 3-Blocked
  public int getOwner()
  {
    validify();
    return Client.tileGetOwner(ptr);
  }

}
