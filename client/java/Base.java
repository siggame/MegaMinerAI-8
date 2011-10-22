import com.sun.jna.Pointer;

///The information on the base
class Base extends Mappable 
{
  public Base(Pointer p)
  {
    super(p);
  }
  boolean validify()
  {
    if(iteration == BaseAI.iteration) return true;
    for(int i = 0; i < BaseAI.bases.length; i++)
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
  int spawn(int Level)
  {
    validify();
    return Client.INSTANCE.baseSpawn(ptr, Level);
  }
    
    //getters
    
  ///Unique Identifier
  public int getId()
  {
    validify();
    return Client.INSTANCE.baseGetId(ptr);
  }
  ///The x coordinate
  public int getX()
  {
    validify();
    return Client.INSTANCE.baseGetX(ptr);
  }
  ///The y cooridnate
  public int getY()
  {
    validify();
    return Client.INSTANCE.baseGetY(ptr);
  }
  ///Whose base this is, all your base are belong to who
  public int getOwner()
  {
    validify();
    return Client.INSTANCE.baseGetOwner(ptr);
  }
  ///The number of viruses this base can still spawn this turn
  public int getSpawnsLeft()
  {
    validify();
    return Client.INSTANCE.baseGetSpawnsLeft(ptr);
  }

}
