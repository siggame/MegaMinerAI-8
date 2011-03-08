import com.sun.jna.Pointer;

///A generic port
class Port: extends Mappable 
{
  Pointer ptr;
  int ID;
  int iteration;
  public Port(Pointer p)
  {
    ptr = p;
    ID = Client.INSTANCE.portGetId(ptr);
    iteration = BaseAI.iteration;
  }

  boolean validify()
  {
    if(iteration == BaseAI.iteration) return true;
    for(int i = 0; i < BaseAI.ports.length; i++)
    {
      if(BaseAI.ports[i].ID == ID)
      {
        ptr = BaseAI.ports[i].ptr;
        iteration = BaseAI.iteration;
        return true;
      }
    }
    throw new ExistentialError();
  }
    
    //commands
    
  ///Creates a Pirate at the calling Port
  int createPirate()
  {
    validify();
    return Client.INSTANCE.portCreatePirate(ptr);
  }
  ///Creates a Ship at the calling Port
  int createShip()
  {
    validify();
    return Client.INSTANCE.portCreateShip(ptr);
  }
    
    //getters
    
  ///Unique Identifier
  public int getId()
  {
    validify();
    return Client.INSTANCE.portGetId(ptr);
  }
  ///The X position of the top left corner of this object.  X is horizontal
  public int getX()
  {
    validify();
    return Client.INSTANCE.portGetX(ptr);
  }
  ///The Y position of the top left corner of this object.  Y is vertical
  public int getY()
  {
    validify();
    return Client.INSTANCE.portGetY(ptr);
  }
  ///The ownder of the port
  public int getOwner()
  {
    validify();
    return Client.INSTANCE.portGetOwner(ptr);
  }

}
