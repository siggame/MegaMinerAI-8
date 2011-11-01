using System;
using System.Runtime.InteropServices;


///Stores information about a player in the game
public class Player
{
  public IntPtr ptr;
  protected int ID;
  protected int iteration;
  
  public Player()
  {
  }
  
  public Player(IntPtr p)
  {
    ptr = p;
    ID = Client.playerGetId(ptr);
    iteration = BaseAI.iteration;
  }

  public bool validify()
  {
    if(iteration == BaseAI.iteration) return true;
    for(int i = 0; i < BaseAI.players.Length; i++)
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
  public int talk(string message)
  {
    validify();
    return Client.playerTalk(ptr, message);
  }
    
    //getters
    
  ///Unique Identifier
  public int getId()
  {
    validify();
    return Client.playerGetId(ptr);
  }
  ///Player's Name
  public string getPlayerName()
  {
    validify();
    return Client.playerGetPlayerName(ptr);
  }
  ///Player's points, one with more at end of game wins
  public int getByteDollars()
  {
    validify();
    return Client.playerGetByteDollars(ptr);
  }
  ///Player's machine cycles, used to create new Virus's
  public int getCycles()
  {
    validify();
    return Client.playerGetCycles(ptr);
  }
  ///The amount of time this player has before timing out
  public int getTime()
  {
    validify();
    return Client.playerGetTime(ptr);
  }

}
