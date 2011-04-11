using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;

///The class implementing gameplay logic.
class AI : BaseAI
{
   
  public override string username()
  {
    return "Shell AI";
  }
  public override string password()
  {
    return "password";
  }

  
 public List<List<bool>> land = new List<List<bool>>();
 public List<List<bool>> port = new List<List<bool>>();

  

  public void objectCheck()
  {
      Console.WriteLine("--Base AI variables--");
      Console.Write("turnNumber\t"); Console.Write(turnNumber()); Console.WriteLine("");

      ///Player Number; either 0 or 1
      Console.Write("playerID\t"); Console.Write(playerID()); Console.WriteLine("");

      ///What number game this is for the server
      Console.Write("gameNumber\t"); Console.Write(gameNumber()); Console.WriteLine("");
      ///Player 0's time remaining
      Console.Write("player0Time\t"); Console.Write(players[0].getTime()); Console.WriteLine("");
      ///Player 1's time remaining
      Console.Write("player1Time\t"); Console.Write(players[1].getTime()); Console.WriteLine("");
      ///Player 0's name
      Console.Write("player0Name\t"); Console.Write(players[0].getPlayerName()); Console.WriteLine("");
      ///Player 1's name
      Console.Write("player1Name\t"); Console.Write(players[1].getPlayerName()); Console.WriteLine("");
      /////The cost of a pirate
      Console.Write("pirateCost\t"); Console.Write(pirateCost()); Console.WriteLine("");
      /////The cost of a ship
      Console.Write("shipCost\t"); Console.Write(shipCost()); Console.WriteLine("");
      Console.Write("mapSize\t"); Console.Write(mapSize()); Console.WriteLine("");
      Console.Write("baordY\t"); Console.Write(mapSize()); Console.WriteLine("");
      Console.Write("--Object counts--"); Console.WriteLine("");
      Console.Write("Pirates : "); Console.WriteLine(pirates.Length); Console.WriteLine("");
      ////displayPirates();
      Console.Write("Ports   : "); Console.Write(ports.Length); Console.WriteLine("");
      ////displayPorts();
      Console.Write("Ships   : "); Console.Write(ships.Length); Console.WriteLine("");
      ////displayShips();
      Console.Write("Tiles   : "); Console.Write(tiles.Length); Console.WriteLine("");
      ////displayTiles();
      Console.Write("Treasure: "); Console.Write(treasures.Length); Console.WriteLine("");
      ////displayTreasure();
  }

public void displayPirates()
{
  for(Int32 i=0;i<pirates.Length;i++)
  {
    ///Unique Identifier
    Console.Write("\tPirate ID\t"); Console.Write(pirates[i].getId() ); 
    ///The X position of this object.  X is horizontal, with 0,0 as the top left corner
    Console.Write("\tX\t"); Console.Write(pirates[i].getX() ); 
    ///The Y position of this object.  Y is vertical, with 0,0 as the top left corner
    Console.Write("\tY\t"); Console.Write(pirates[i].getY() ); 
    ///The owner of the unit
    Console.Write("\tOwner\t"); Console.Write(pirates[i].getOwner() ); 
    ///health of the unit
    Console.Write("\tHealth\t"); Console.Write(pirates[i].getHealth() ); 
    ///attacking strength of the unit
    Console.Write("\tStrength\t"); Console.Write(pirates[i].getStrength());
    Console.WriteLine("");
  }
}

public void displayPorts()
{
  for(Int32 i=0; i<ports.Length; i++)
  {
    ///Unique Identifier
    Console.Write("\tPortID\t"); Console.Write(ports[i].getId());
    ///The X position of this object.  X is horizontal, with 0,0 as the top left corner
    Console.Write("\tX\t"); Console.Write(ports[i].getX());
    ///The Y position of this object.  Y is vertical, with 0,0 as the top left corner
    Console.Write("\tY\t"); Console.Write(ports[i].getY());
    ///The ownder of the port
    Console.Write("\tOwner\t"); Console.Write(ports[i].getOwner());
    Console.WriteLine("");
  }
}

public void displayShips()
{
  for(Int32 i=0; i<ships.Length; i++)
  {
    ///Unique Identifier
    Console.Write("\tShip ID\t"); Console.Write(ships[i].getId());
    ///The X position of this object.  X is horizontal, with 0,0 as the top left corner
    Console.Write("\tX\t"); Console.Write(ships[i].getX());
    ///The Y position of this object.  Y is vertical, with 0,0 as the top left corner
    Console.Write("\tY\t"); Console.Write(ships[i].getY());
    ///The owner of the unit
    Console.Write("\tOwner\t"); Console.Write(ships[i].getOwner());
    ///health of the unit
    Console.Write("\tHealth\t"); Console.Write(ships[i].getHealth());
    ///attacking strength of the unit
    Console.Write("\tStrength\t"); Console.Write(ships[i].getStrength());
    Console.WriteLine("");
  }
}

public void displayTiles()
{
  for(Int32 i=0; i<tiles.Length; i++)
  {
    ///Unique Identifier
    Console.Write("\tTile ID\t"); Console.Write(tiles[i].getId());
    ///The X position of this object.  X is horizontal, with 0,0 as the top left corner
    Console.Write("\tX\t"); Console.Write(tiles[i].getX());
    ///The Y position of this object.  Y is vertical, with 0,0 as the top left corner
    Console.Write("\tY\t"); Console.Write(tiles[i].getY());
    ///land = 0, water = 1
    Console.Write("\tType\t"); Console.Write(tiles[i].getType());
    Console.WriteLine("");
  }
}

public void displayTreasure()
{
  for(Int32 i=0; i<treasures.Length; i++)
  {
    ///Unique Identifier
    Console.Write("\tTreas ID\t"); Console.Write(treasures[i].getId());
    ///The X position of this object.  X is horizontal, with 0,0 as the top left corner
    Console.Write("\tX\t"); Console.Write(treasures[i].getX());
    ///The Y position of this object.  Y is vertical, with 0,0 as the top left corner
    Console.Write("\tY\t"); Console.Write(treasures[i].getY());
    //TODO Pirate carring treasure
    Console.WriteLine("");
  }
}

  //This function is called each time it is your turn
  //Return true to end your turn, return false to ask the server for updated information
  public override bool run()
  {
    Console.Write("Starting turn: "); Console.Write(turnNumber()); Console.WriteLine("");
    //objectCheck();
    //displayPirates();
    //displayPorts();
    //displayShips();
    //displayTiles();
    //displayTreasure();
    return true;
  }

  //This function is called once, before your first turn
  public override void init() 
  {
      Random rand = new Random();
      Console.WriteLine("Initialization called");
      objectCheck();
      //land = vector<vector<bool> >(mapSize(),vector<bool>(mapSize(),false));
  //vector<vector<bool> > tile(mapSize(),vector<bool>(mapSize(),false));
  //port = vector<vector<int> >(mapSize(),vector<int>(mapSize(),-1));
  //for(Int32 i=0;i<tiles.size();i++)
  //{
  //  land[tiles[i].x()][tiles[i].y()]= tiles[i].type()==0;
  //  tile[tiles[i].x()][tiles[i].y()]= true;
  //}
  //for(size_t i=0;i<ports.size();i++)
  //{
  //  if(!land[ports[i].x()][ports[i].y()])
  //  {
  //    cout<<"A port isn't land!"<<endl;
  //    string trash;
  //    cin>>trash;
  //    land[ports[i].x()][ports[i].y()]=true;
  //  }
  //  port[ports[i].x()][ports[i].y()]=ports[i].owner();
  //}
  //for(size_t i=0;i<land.size();i++)
  //{
  //  for(size_t j=0;j<land[i].size();j++)
  //  {
  //    if(!tile[i][j])
  //    {
  //      cout<<"TILE MISSING!"<<endl;
  //      throw "SHIT FIT";
  //    }
  //    cout<<(land[i][j]?"X":".")<<" ";
  //  }
  //  cout<<endl;
  //}
  //for(size_t i=0;i<pirates.size();i++)
  //{
  //  if(port[pirates[i].x()][pirates[i].y()]==-1)
  //  {
  //    cout<<"A pirate did start not on a port!"<<endl;
  //  }
  //  else if(port[pirates[i].x()][pirates[i].y()]!=pirates[i].owner())
  //  {
  //    cout<<"A pirate owned by player: "<<pirates[i].owner()<<" Started on port owned by player: "<<port[pirates[i].x()][pirates[i].y()]<<endl;
  //  }
  //}
  //displayPorts();
  }

  //This function is called once, after your last turn
  public override void end() 
  {
      Console.ReadLine();
  }
  
  
  public AI(IntPtr c) : base(c)
  {}
}
