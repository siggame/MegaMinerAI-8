import com.sun.jna.Pointer;
import java.util.*;
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
  Random generator = new Random();
  int xoff[] = {0, 1, 0, -1};
  int yoff[] = {1, 0, -1, 0};

  //This function is called each time it is your turn
  //Return true to end your turn, return false to ask the server for updated information
  public boolean run()
  {
    System.out.println("Turn Number: "+turnNumber());
    printPirates();
    int myPort=0;
    while(ports[myPort].getOwner() != playerID())myPort++;
    for(int i=0;i<players[playerID()].getGold();i+=pirateCost())
    {
    //  ports[myPort].createPirate();
    }
    
    ArrayList<Integer> enemies= new ArrayList<Integer>();
    for(int i=0;i<pirates.length;i++)
    {
      if(pirates[i].getOwner() != playerID())
      {
        enemies.add(i);
      }
    }
    
    for(int i=0;i<pirates.length;i++)
    {
      if(pirates[i].getOwner() == playerID())
      {
        int target = generator.nextInt(enemies.size());
        target=0;
        if(pirates[enemies.get(target)].getOwner()==playerID())
        {
          System.out.println("FUCK");
        }
        Tile path[] = getPath(pirates[i].getX(), pirates[i].getY(), 
                              pirates[enemies.get(target)].getX(), pirates[enemies.get(target)].getY(),0);
        if(path.length>1)
        {
          System.out.println("Move");
          pirates[i].move(path[0].getX(),path[0].getY());
        }
        else if(path.length==1)
        {
          System.out.println("Attack");
          pirates[i].attack(pirates[enemies.get(target)]);
        }
      }
    }
    return true;
  }
  private void printPirates()
  {
    for(int i=0;i<pirates.length;i++)
    {
      if(playerID()==pirates[i].getOwner())
      {
        printPirate(i);
        System.out.println();
      }
      
    }
  }
  
  private void printPirate(int i)
  {
    System.out.print("pirates["+i+"]=(id "+pirates[i].getId()
                                 +") (x "+pirates[i].getX()
                                 +") ("+pirates[i].getY()
                                 +") ("+pirates[i].getOwner()
                                 +") ("+pirates[i].getHealth()
                                 +") ("+pirates[i].getStrength()
                                 +")"); 
  }

  //This function is called once, before your first turn
  public void init() { }

  //This function is called once, after your last turn
  public void end() {}
  
  
  public AI(Pointer c)
  {
    super(c);
  }
}
