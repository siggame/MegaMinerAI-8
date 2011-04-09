using System;
using System.Runtime.InteropServices;

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

  public void objectCheck()
  {
      Console.WriteLine("--Base AI variables--");
      Console.Write("turnNumber\t"); Console.Write(turnNumber()); Console.WriteLine("");

      ///Player Number; either 0 or 1
      Console.Write("playerID\t"); Console.Write(playerID()); Console.WriteLine("");

      ///What number game this is for the server
      Console.Write("gameNumber\t"); Console.Write(gameNumber()); Console.WriteLine("");
      ///Player 0's time remaining
      Console.Write("player0Time\t"); Console.Write(players[0].time()); Console.WriteLine("");
      ///Player 1's time remaining
      Console.Write("player1Time\t"); Console.Write(players[1].time()); Console.WriteLine("");
      /////Player 0's name
      //Console.Write("player0Name\t") << players[0].playerName() Console.WriteLine("");
      /////Player 1's name
      //Console.Write("player1Name\t") << players[1].playerName() Console.WriteLine("");
      /////The cost of a pirate
      //Console.Write("pirateCost\t" << pirateCost() Console.WriteLine("");
      /////The cost of a ship
      //Console.Write("shipCost\t" << shipCost() Console.WriteLine("");
      //Console.Write("mapSize\t" << mapSize() Console.WriteLine("");
      //Console.Write("baordY\t" << mapSize() Console.WriteLine("");
      //Console.Write("--Object counts--" Console.WriteLine("");
      //Console.Write("Pirates : " << pirates.size() << endl;
      ////displayPirates();
      //Console.Write("Ports   : " << ports.size() << endl;
      ////displayPorts();
      //Console.Write("Ships   : " << ships.size() << endl;
      ////displayShips();
      //Console.Write("Tiles   : " << tiles.size() << endl;
      ////displayTiles();
      //Console.Write("Treasure: " << treasures.size() << endl;
      ////displayTreasure();
  }

  //This function is called each time it is your turn
  //Return true to end your turn, return false to ask the server for updated information
  public override bool run()
  {
    return true;
  }

  //This function is called once, before your first turn
  public override void init() 
  {
      Random rand = new Random();
      Console.WriteLine("Initialization called");
      objectCheck();
  }

  //This function is called once, after your last turn
  public override void end() {}
  
  
  public AI(IntPtr c) : base(c)
  {}
}
