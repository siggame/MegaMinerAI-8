using System;
using System.Runtime.InteropServices;


///Stores the information about a virus
public class Virus: Mappable 
{
  
  public Virus()
  {
  }
  
  public Virus(IntPtr p)
  {
    ptr = p;
    ID = Client.virusGetId(ptr);
    iteration = BaseAI.iteration;
  }

  public override bool validify()
  {
    if(iteration == BaseAI.iteration) return true;
    for(int i = 0; i < BaseAI.viruss.Length; i++)
    {
      if(BaseAI.viruss[i].ID == ID)
      {
        ptr = BaseAI.viruss[i].ptr;
        iteration = BaseAI.iteration;
        return true;
      }
    }
    throw new ExistentialError();
  }
    
    //commands
    
  ///Moves a unit to the given (x,y) position
  public int move(int x, int y)
  {
    validify();
    return Client.virusMove(ptr, x, y);
  }
    
    //getters
    
  ///Unique Identifier
  public new int getId()
  {
    validify();
    return Client.virusGetId(ptr);
  }
  ///The x coordinate
  public new int getX()
  {
    validify();
    return Client.virusGetX(ptr);
  }
  ///The y cooridnate
  public new int getY()
  {
    validify();
    return Client.virusGetY(ptr);
  }
  ///The owner of this Virus
  public int getOwner()
  {
    validify();
    return Client.virusGetOwner(ptr);
  }
  ///The Virus's level
  public int getLevel()
  {
    validify();
    return Client.virusGetLevel(ptr);
  }

}
