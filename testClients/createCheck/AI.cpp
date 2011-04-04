#include "AI.h"
#include "util.h"

AI::AI(Connection* conn) : BaseAI(conn) {}

const char* AI::username()
{
  return "Shell AI";
}

const char* AI::password()
{
  return "password";
}

//This function is run once, before your first turn.
void AI::init()
{
  srand(time(NULL));
  cout<<"Initialization called"<<endl;
  objectCheck();
}

//This function is called each time it is your turn.
//Return true to end your turn, return false to ask the server for updated information.
bool AI::run()
{
  cout<<"Starting turn: "<<turnNumber()<<endl;
  for(size_t i=0;i<players.size();i++)
  {
    if(players[i].id()!= i)
    {
      cout<<"Player["<<i<<"].id()= "<<players[i].id()<<" Gold: "<<players[i].gold()<<endl;
//      throw "SHIT";
    }
  }
  //objectCheck();
  displayPirates();
  for(size_t i=0;i<ports.size();i++)
  {
    if((pirateCost()<=players[1].gold()) && ports[i].owner()!= playerID())
    {
      ports[i].createPirate();
    }
    //ports[i].createShip();
  }
  
  /*
  for(size_t i=0;i<pirates.size();i++)
  {
    pirates[i].buildPort();
  }
  */
  return true;
}

void AI::displayPirates()
{
  for(size_t i=0;i<pirates.size();i++)
  {
    ///Unique Identifier
    cout<<"\tID\t"<<pirates[i].id();
    ///The X position of this object.  X is horizontal, with 0,0 as the top left corner
    cout<<"\tX\t"<<pirates[i].x();
    ///The Y position of this object.  Y is vertical, with 0,0 as the top left corner
    cout<<"\tY\t"<<pirates[i].y();
    ///The owner of the unit
    cout<<"\tOwner\t"<<pirates[i].owner();
    ///health of the unit
    cout<<"\tHealth\t"<<pirates[i].health();
    ///attacking strength of the unit
    cout<<"\tStrength\t"<<pirates[i].strength();
    cout<<endl;
  }
}
void AI::displayPorts()
{
  for(size_t i=0;i<ports.size();i++)
  {
    ///Unique Identifier
    cout<<"\tID\t"<<ports[i].id();
    ///The X position of this object.  X is horizontal, with 0,0 as the top left corner
    cout<<"\tX\t"<<ports[i].x();
    ///The Y position of this object.  Y is vertical, with 0,0 as the top left corner
    cout<<"\tY\t"<<ports[i].y();
    ///The ownder of the port
    cout<<"\tOwner\t"<<ports[i].owner();
    cout<<endl;
  }
}

void AI::displayShips()
{
  for(size_t i=0;i<ships.size();i++)
  {
    ///Unique Identifier
    cout<<"\tID\t"<<ships[i].id();
    ///The X position of this object.  X is horizontal, with 0,0 as the top left corner
    cout<<"\tX\t"<<ships[i].x();
    ///The Y position of this object.  Y is vertical, with 0,0 as the top left corner
    cout<<"\tY\t"<<ships[i].y();
    ///The owner of the unit
    cout<<"\tOwner\t"<<ships[i].owner();
    ///health of the unit
    cout<<"\tHealth\t"<<ships[i].health();
    ///attacking strength of the unit
    cout<<"\tStrength\t"<<ships[i].strength();
    cout<<endl;
  }
}

void AI::displayTiles()
{
  for(size_t i=0;i<tiles.size();i++)
  {
    ///Unique Identifier
    cout<<"\tID\t"<<tiles[i].id();
    ///The X position of this object.  X is horizontal, with 0,0 as the top left corner
    cout<<"\tX\t"<<tiles[i].x();
    ///The Y position of this object.  Y is vertical, with 0,0 as the top left corner
    cout<<"\tY\t"<<tiles[i].y();
    ///land = 0, water = 1
    cout<<"\tType\t"<<tiles[i].type();
    cout<<endl;
  }
}

void AI::displayTreasure()
{
  for(size_t i=0;i<treasures.size();i++)
  {
    ///Unique Identifier
    cout<<"\tID\t"<<treasures[i].id();
    ///The X position of this object.  X is horizontal, with 0,0 as the top left corner
    cout<<"\tX\t"<<treasures[i].x();
    ///The Y position of this object.  Y is vertical, with 0,0 as the top left corner
    cout<<"\tY\t"<<treasures[i].y();
    //TODO Pirate carring treasure
    cout<<endl;
  }
}
void AI::objectCheck()
{
  cout<<"--Base AI variables--"<<endl;
  cout<<"turnNumber\t"<<turnNumber()<<endl;
  ///Player Number; either 0 or 1
  cout<<"playerID\t"<<playerID()<<endl;
  ///What number game this is for the server
  cout<<"gameNumber\t"<<gameNumber()<<endl;
  ///Player 0's time remaining
  cout<<"player0Time\t"<<players[0].time()<<endl;
  ///Player 1's time remaining
  cout<<"player1Time\t"<<players[1].time()<<endl;
  ///Player 0's name
  cout<<"player0Name\t"<<players[0].playerName()<<endl;
  ///Player 1's name
  cout<<"player1Name\t"<<players[1].playerName()<<endl;
  ///The cost of a pirate
  cout<<"pirateCost\t"<<pirateCost()<<endl;
  ///The cost of a ship
  cout<<"shipCost\t"<<shipCost()<<endl;
  cout<<"mapSize\t"<<mapSize()<<endl;
  cout<<"baordY\t"<<mapSize()<<endl;
  cout<<"--Object counts--"<<endl;
  cout<<"Pirates : "<<pirates.size()<<endl;
  //displayPirates();
  cout<<"Ports   : "<<ports.size()<<endl;
  //displayPorts();
  cout<<"Ships   : "<<ships.size()<<endl;
  //displayShips();
  cout<<"Tiles   : "<<tiles.size()<<endl;
  //displayTiles();
  cout<<"Treasure: "<<treasures.size()<<endl;
  //displayTreasure();
}

//This function is run once, after your last turn.
void AI::end()
{
  cout<<"End Called"<<endl;
  objectCheck();
}
