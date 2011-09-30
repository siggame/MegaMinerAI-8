import com.sun.jna.Pointer;

///The base object for all mappable things
abstract class Mappable
{
  Pointer ptr;
  int ID;
  int iteration;
  public Mappable(Pointer p)
  {
    ptr = p;
    ID = Client.INSTANCE.mappableGetId(ptr);
    iteration = BaseAI.iteration;
  }
  abstract boolean validify();
    
    //commands
    
    
    //getters
    
  ///Unique Identifier
  public int getId()
  {
    validify();
    return Client.INSTANCE.mappableGetId(ptr);
  }
  ///The x coordinate
  public int getX()
  {
    validify();
    return Client.INSTANCE.mappableGetX(ptr);
  }
  ///The y cooridnate
  public int getY()
  {
    validify();
    return Client.INSTANCE.mappableGetY(ptr);
  }

}
