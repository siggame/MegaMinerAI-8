import com.sun.jna.Pointer;

///Stores the information about a virus
class Virus extends Mappable 
{
  public Virus(Pointer p)
  {
    super(p);
  }
  boolean validify()
  {
    if(iteration == BaseAI.iteration) return true;
    for(int i = 0; i < BaseAI.viruss.length; i++)
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
  int move(int x, int y)
  {
    validify();
    return Client.INSTANCE.virusMove(ptr, x, y);
  }
  ///Allows a Virus to display a message to the screen.
  int talk(String message)
  {
    validify();
    return Client.INSTANCE.virusTalk(ptr, message);
  }
    
    //getters
    
  ///Unique Identifier
  public int getId()
  {
    validify();
    return Client.INSTANCE.virusGetId(ptr);
  }
  ///The x coordinate
  public int getX()
  {
    validify();
    return Client.INSTANCE.virusGetX(ptr);
  }
  ///The y cooridnate
  public int getY()
  {
    validify();
    return Client.INSTANCE.virusGetY(ptr);
  }
  ///The owner of this Virus
  public int getOwner()
  {
    validify();
    return Client.INSTANCE.virusGetOwner(ptr);
  }
  ///The Virus's level
  public int getLevel()
  {
    validify();
    return Client.INSTANCE.virusGetLevel(ptr);
  }
  ///The number of times this virus can still move
  public int getMovesLeft()
  {
    validify();
    return Client.INSTANCE.virusGetMovesLeft(ptr);
  }

}
