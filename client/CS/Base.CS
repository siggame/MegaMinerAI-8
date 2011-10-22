using System;
using System.Runtime.InteropServices;


///The information on the base
public class Base: Mappable 
{
  
  public Base()
  {
  }
  
  public Base(IntPtr p)
  {
    ptr = p;
    ID = Client.baseGetId(ptr);
    iteration = BaseAI.iteration;
  }

  public override bool validify()
  {
    if(iteration == BaseAI.iteration) return true;
    for(int i = 0; i < BaseAI.bases.Length; i++)
    {
      if(BaseAI.bases[i].ID == ID)
      {
        ptr = BaseAI.bases[i].ptr;
        iteration = BaseAI.iteration;
        return true;
      }
    }
    throw new ExistentialError();
  }
    
    //commands
    
  ///Creates a Virus on the base with certain level.
  public int spawn(int Level)
  {
    validify();
    return Client.baseSpawn(ptr, Level);
  }
    
    //getters
    
  ///Unique Identifier
  public new int getId()
  {
    validify();
    return Client.baseGetId(ptr);
  }
  ///The x coordinate
  public new int getX()
  {
    validify();
    return Client.baseGetX(ptr);
  }
  ///The y cooridnate
  public new int getY()
  {
    validify();
    return Client.baseGetY(ptr);
  }
  ///Whose base this is, all your base are belong to who
  public int getOwner()
  {
    validify();
    return Client.baseGetOwner(ptr);
  }
  ///The number of viruses this base can still spawn this turn
  public int getSpawnsLeft()
  {
    validify();
    return Client.baseGetSpawnsLeft(ptr);
  }

}
