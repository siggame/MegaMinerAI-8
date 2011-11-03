import com.sun.jna.Pointer;

///Stores information about a player in the game
class Player
{
  Pointer ptr;
  int ID;
  int iteration;
  public Player(Pointer p)
  {
    ptr = p;
    ID = Client.INSTANCE.playerGetId(ptr);
    iteration = BaseAI.iteration;
  }
  boolean validify()
  {
    if(iteration == BaseAI.iteration) return true;
    for(int i = 0; i < BaseAI.players.length; i++)
    {
      if(BaseAI.players[i].ID == ID)
      {
        ptr = BaseAI.players[i].ptr;
        iteration = BaseAI.iteration;
        return true;
      }
    }
    throw new ExistentialError();
  }
    
    //commands
    
  ///Allows a player to display a message to the screen.
  int talk(String message)
  {
    validify();
    return Client.INSTANCE.playerTalk(ptr, message);
  }
    
    //getters
    
  ///Unique Identifier
  public int getId()
  {
    validify();
    return Client.INSTANCE.playerGetId(ptr);
  }
  ///Player's Name
  public String getPlayerName()
  {
    validify();
    return Client.INSTANCE.playerGetPlayerName(ptr);
  }
  ///Player's points, one with more at end of game wins
  public int getByteDollars()
  {
    validify();
    return Client.INSTANCE.playerGetByteDollars(ptr);
  }
  ///Player's machine cycles, used to create new Virus's
  public int getCycles()
  {
    validify();
    return Client.INSTANCE.playerGetCycles(ptr);
  }
  ///The amount of time this player has before timing out
  public int getTime()
  {
    validify();
    return Client.INSTANCE.playerGetTime(ptr);
  }

}
