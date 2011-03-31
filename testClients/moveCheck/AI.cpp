#include "AI.h"
#include "util.h"

#include <iostream>
using namespace std;
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
  land = vector<vector<bool> >(mapSize(),vector<bool>(mapSize(),false));
  for(size_t i=0;i<tiles.size();i++)
  {
    land[tiles[i].x()][tiles[i].y()]= tiles[i].type()==0;
  }
  for(size_t i=0;i<ports.size();i++)
  {
    if(!land[ports[i].x()][ports[i].y()])
    {
      cout<<"A port isn't land!"<<endl;
      string trash;
      cin>>trash;
      land[ports[i].x()][ports[i].y()]=true;
    }
  }
  for(size_t i=0;i<land.size();i++)
  {
    for(size_t j=0;j<land[i].size();j++)
    {
      cout<<(land[i][j]?"X":".")<<" ";
    }
    cout<<endl;
  }
}

//This function is called each time it is your turn.
//Return true to end your turn, return false to ask the server for updated information.
bool AI::run()
{
  cout<<"Starting turn: "<<turnNumber()<<endl;
  string trash;
  
//  objectCheck();
  for(size_t i=0;i<pirates.size();i++)
  {
    //pirates[i].move(rand()%mapSize(), rand()%mapSize());
    if(pirates[i].owner() == playerID())
    {
      if(!land[pirates[i].x()][pirates[i].y()])
      {
        cout<<"A pirate is in the water!"<<endl;
        cin>>trash;
      }
      //pirates[i].move(rand()%40, rand()%40);
      //int dir=rand()%4;
      //pirates[i].move(pirates[i].x()+xoff[dir],pirates[i].y()+yoff[dir]);
      bool moved=false;
      for(size_t dir=0;dir<4&&!moved; dir++)
      {
        int x=pirates[i].x()+xoff[dir];
        int y=pirates[i].y()+yoff[dir];
        if(!land[x][y])
        {
          cout<<"Pirate: "<<pirates[i].id()<<" moving onto water"<<endl;
          pirates[i].move(x,y);
          moved=true;
        }
      }
      if(!moved)
      {
        int dir=rand()%4;
        pirates[i].move(pirates[i].x()+xoff[dir],pirates[i].y()+yoff[dir]);
      }
    }
  }
  displayPirates();
  /*
  for(size_t i=0;i<ships.size();i++)
  {
    //ships[i].move(rand()%mapSize(), rand()%mapSize());
    ships[i].move(rand()%40, rand()%40);
    ships[i].move(ships[i].x()+xoff[rand()%4],ships[i].y()+yoff[rand()%4]);
  }
  */
  
 // cin>>trash;
  return true;
}

void AI::displayPirates()
{
  for(size_t i=0;i<pirates.size();i++)
  {
    if(pirates[i].owner()==playerID())
    {
    ///Unique Identifier
    cout<<"\tID\t"<<pirates[i].id()<<endl;
    ///The X position of this object.  X is horizontal, with 0,0 as the top left corner
    cout<<"\tX\t"<<pirates[i].x()<<endl;
    ///The Y position of this object.  Y is vertical, with 0,0 as the top left corner
    cout<<"\tY\t"<<pirates[i].y()<<endl;
    ///The owner of the unit
    cout<<"\tOwner\t"<<pirates[i].owner()<<endl;
    ///health of the unit
    cout<<"\tHealth\t"<<pirates[i].health()<<endl;
    ///attacking strength of the unit
    cout<<"\tStrength\t"<<pirates[i].strength()<<endl;
    cout<<endl;
    }
  }
}
void AI::displayPorts()
{
  for(size_t i=0;i<ports.size();i++)
  {
    ///Unique Identifier
    cout<<"\tID\t"<<ports[i].id()<<endl;
    ///The X position of this object.  X is horizontal, with 0,0 as the top left corner
    cout<<"\tX\t"<<ports[i].x()<<endl;
    ///The Y position of this object.  Y is vertical, with 0,0 as the top left corner
    cout<<"\tY\t"<<ports[i].y()<<endl;
    ///The ownder of the port
    cout<<"\tOwner\t"<<ports[i].owner()<<endl;
    cout<<endl;
  }
}

void AI::displayShips()
{
  for(size_t i=0;i<ships.size();i++)
  {
    ///Unique Identifier
    cout<<"\tID\t"<<ships[i].id()<<endl;
    ///The X position of this object.  X is horizontal, with 0,0 as the top left corner
    cout<<"\tX\t"<<ships[i].x()<<endl;
    ///The Y position of this object.  Y is vertical, with 0,0 as the top left corner
    cout<<"\tY\t"<<ships[i].y()<<endl;
    ///The owner of the unit
    cout<<"\tOwner\t"<<ships[i].owner()<<endl;
    ///health of the unit
    cout<<"\tHealth\t"<<ships[i].health()<<endl;
    ///attacking strength of the unit
    cout<<"\tStrength\t"<<ships[i].strength()<<endl;
    cout<<endl;
  }
}

void AI::displayTiles()
{
  for(size_t i=0;i<tiles.size();i++)
  {
    ///Unique Identifier
    cout<<"\tID\t"<<tiles[i].id()<<endl;
    ///The X position of this object.  X is horizontal, with 0,0 as the top left corner
    cout<<"\tX\t"<<tiles[i].x()<<endl;
    ///The Y position of this object.  Y is vertical, with 0,0 as the top left corner
    cout<<"\tY\t"<<tiles[i].y()<<endl;
    ///land = 0, water = 1
    cout<<"\tType\t"<<tiles[i].type()<<endl;
    cout<<endl;
  }
}

void AI::displayTreasure()
{
  for(size_t i=0;i<treasures.size();i++)
  {
    ///Unique Identifier
    cout<<"\tID\t"<<treasures[i].id()<<endl;
    ///The X position of this object.  X is horizontal, with 0,0 as the top left corner
    cout<<"\tX\t"<<treasures[i].x()<<endl;
    ///The Y position of this object.  Y is vertical, with 0,0 as the top left corner
    cout<<"\tY\t"<<treasures[i].y()<<endl;
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
  ///The cost of a ship
  cout<<"ShipCost\t"<<shipCost()<<endl;
  cout<<"boardX\t"<<mapSize()<<endl;
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
