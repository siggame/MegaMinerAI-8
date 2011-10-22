using System;
using System.Runtime.InteropServices;


///The base object for all mappable things
public abstract class Mappable
{
  public IntPtr ptr;
  protected int ID;
  protected int iteration;
  
  public Mappable()
  {
  }
  
  public Mappable(IntPtr p)
  {
    ptr = p;
    ID = Client.mappableGetId(ptr);
    iteration = BaseAI.iteration;
  }

  public abstract bool validify();
    
    //commands
    
    
    //getters
    
  ///Unique Identifier
  public int getId()
  {
    validify();
    return Client.mappableGetId(ptr);
  }
  ///The x coordinate
  public int getX()
  {
    validify();
    return Client.mappableGetX(ptr);
  }
  ///The y cooridnate
  public int getY()
  {
    validify();
    return Client.mappableGetY(ptr);
  }

}
