import com.sun.jna.Pointer;

///The class implementing gameplay logic.
class AI extends BaseAI
{
  public String username()
  {
    return "Shell AI";
  }
  public String password()
  {
    return "password";
  }

  //This function is called each time it is your turn
  //Return true to end your turn, return false to ask the server for updated information
  public boolean run()
  {
    // loop through all of the bases
    for(int i=0;i<bases.length;i++)
    {
      // check if you own that base
      if(bases[i].getOwner() == playerID())
      {
        // check to see if you have enough cycles to spawn a level 0 virus
        if(baseCost() <= players[playerID()].getCycles())
        {
          // spawn a level 0 virus at that base
          bases[i].spawn(0);
        }
      }
    }

    // loop through all of the viruses
    for(int i=0;i<viruses.length;i++)
    {
      // if you own that virus
      if(viruses[i].getOwner() == playerID())
      {
        // if the tile you want to move to is NOT a wall
        if(getTileAtLocation(viruses[i].getX()+1, viruses[i].getY()).getOwner() != 3)
        {
          // move the virus
          viruses[i].move(viruses[i].getX()+1, viruses[i].getY());
        }
      }
    }
    return true;
  }


  //This function is called once, before your first turn
  public void init() {}

  //This function is called once, after your last turn
  public void end() {}
  
  
  public AI(Pointer c)
  {
    super(c);
  }
}
