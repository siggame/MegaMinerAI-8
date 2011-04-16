import com.sun.jna.Pointer;

import java.util.Random;

///The class implementing gameplay logic.
class AI extends BaseAI
{
  Random rand;

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
    System.out.println("Turn: " + turnNumber() + " My ID: " + playerID() + " My Gold: " + players[playerID()].getGold() + "\n");

    // if you have enough gold to buy a pirate
    if(pirateCost() < players[playerID()].getGold())
    {
      // find a port that you own
      for(int p=0;p<ports.length;p++)
      {
        if(ports[p].getOwner()==playerID())
        {
          ports[p].createPirate();
          break;
        }
      }
    }

    // For each pirate in the world
    for(int i=0;i<pirates.length;i++)
    {
      // if I own the pirate
      if(pirates[i].getOwner()==playerID())
      {
        // select a random pirate from the list
        int target = rand.nextInt(pirates.length);
        // Does a naive path finding algorithm that only takes into account tile types, not other blocking problems
        // Takes a start x, start y, end x, end y, and a tile type you wish to path on
        Tile[] path = getPath(pirates[i].getX(),pirates[i].getY(),pirates[target].getX(),pirates[target].getY(),0);
        // for all but the last step of the path, while I have steps, move
        for(int step=0;step+1<path.length && pirates[i].getMovesLeft()>0;step++)
        {
          pirates[i].move(path[step].getX(),path[step].getY());
        }
        // get the distance between the guys
        int distance = Math.abs(pirates[i].getX() - pirates[target].getX()) + Math.abs(pirates[i].getY()-pirates[target].getY());

        // If the distance is exactly 1 away and I don't own the guy
        if( distance ==1 && pirates[i].getOwner()!=pirates[target].getOwner())
        {
          while(pirates[i].getAttacksLeft()>0)
          {
            // attack the target
            pirates[i].attack(pirates[target]);
          }
        }
      }
    }
    return true;
  }

  //This function is called once, before your first turn
  public void init()
  {
    System.out.println("Initializing");
    rand = new Random();
  }

  //This function is called once, after your last turn
  public void end() {}


  public AI(Pointer c)
  {
    super(c);
  }
}
