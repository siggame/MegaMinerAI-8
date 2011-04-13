#include "AI.h"
#include "util.h"
#include <iostream>
#include <string>
#include <stdlib.h>

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
  //cout<<"Initialization called"<<endl;
  //objectCheck();
  
  //clear the screen when we begin
  cout << "\033[2J\033[1;1H";
}

//This function is called each time it is your turn.
//Return true to end your turn, return false to ask the server for updated information.
bool AI::run()
{
  //cout<<"Starting turn: "<<turnNumber()<<endl;
  //objectCheck();
  
  //clears the screen
  //cout << "\033[2J\033[1;1H";
  cout << "\033[f";
  displayCurrentMatch();
  return true;
}

void AI::displayCurrentMatch()
{
  const int SHIP = 1;
  const int PIRATE = 2;
  const int PORT = 3;
  const int OWNER_RED = 0;
  const int OWNER_BLUE = 1;
  const int OWNER_MERCHANT_A = 2;
  const int OWNER_MERCHANT_B = 3;

  int mapTiles[mapSize()][mapSize()];
  int mapObjects[mapSize()][mapSize()];
  int mapOwners[mapSize()][mapSize()];
  
  //first we display red team
  cout << "\033[22;35m";
  cout << "Player 0: " << players[0].playerName() << " Gold: " << players[0].gold() << "       ";
  cout << "\033[0;37m";
  cout<<"turn: "<< turnNumber() << "        ";
   cout << "\033[01;36m";
  cout << "Player 1: " << players[1].playerName() << " Gold: " << players[1].gold();
  
  for(int i = 0; i < tiles.size(); i++)
  {
    mapTiles[tiles[i].x()][tiles[i].y()] = tiles[i].type();
  }
  
  for(int y = 0; y < mapSize(); y++)
  {
    for(int x = 0; x < mapSize(); x++)
    {
      mapObjects[x][y] = 0;
      mapOwners[x][y] = -1;
    }
  }
  
  for(int i = 0; i < ports.size(); i++)
  {
    mapTiles[ports[i].x()][ports[i].y()] = PORT;
    mapOwners[ports[i].x()][ports[i].y()] = ports[i].owner();
  }
  
  for(int i = 0; i < pirates.size(); i++)
  {
    mapObjects[pirates[i].x()][pirates[i].y()] = PIRATE;
    mapOwners[pirates[i].x()][pirates[i].y()] = pirates[i].owner();
  }
  
  for(int i = 0; i < ships.size(); i++)
  {
    mapObjects[ships[i].x()][ships[i].y()] = SHIP;
    mapOwners[ships[i].x()][ships[i].y()] = ships[i].owner();
  }
  
  
  //displays the map!
  for(int y = 0; y < mapSize(); y++)
  {
    cout << endl;
    
    for(int x = 0; x < mapSize(); x++)
    {
      if(mapTiles[x][y] == 1) //land
      {
        //sets background color to green
        cout << "\033[7;34m";
      }
      else if(mapTiles[x][y] == 0) //land
      {
        //sets background color to blue
        cout << "\033[7;32m";
      }
      else if(mapTiles[x][y] == PORT) //port
      {
        cout << "\033[7;35m";
      }
      
      if(mapOwners == OWNER_RED)
      {
        cout << "\033[22;31m";
      }
      else if(mapOwners[x][y] == OWNER_BLUE)
      {
        cout << "\033[01;36m";
      }
      else if(mapOwners[x][y] == OWNER_MERCHANT_A)
      {
        cout << "\033[0;37m";
      }
      else if(mapOwners[x][y] == OWNER_MERCHANT_B)
      {
        cout << "\033[01;30m";
      }
      
      if(mapObjects[x][y] == PIRATE)
      {
        cout << " P";
      }
      else if(mapObjects[x][y] == SHIP)
      {
        cout << " S";
      }
      else
      {
        cout << "  ";
      }
      
      //reset color to defaults
      cout << "\033[0m";
    }
  }
}

void AI::displayPirates()
{
  for(size_t i=0;i<pirates.size();i++)
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
  vector<int> count(2,0);
  for(size_t i=0;i<tiles.size();i++)
  {
    /*
    ///Unique Identifier
    cout<<"\tID\t"<<tiles[i].id()<<endl;
    ///The X position of this object.  X is horizontal, with 0,0 as the top left corner
    cout<<"\tX\t"<<tiles[i].x()<<endl;
    ///The Y position of this object.  Y is vertical, with 0,0 as the top left corner
    cout<<"\tY\t"<<tiles[i].y()<<endl;
    ///land = 0, water = 1
    cout<<"\tType\t"<<tiles[i].type()<<endl;
    cout<<endl;
    */
    if(tiles[i].type()>count.size())
    {
      count.resize(tiles[i].type());
    }
    count[tiles[i].type()]++;
  }
  cout<<"\ttype\tnumber"<<endl;
  for(size_t i=0;i<count.size();i++)
  {
    cout<<"\t"<<i<<")\t"<<count[i]<<endl;
  }
  cout<<endl;
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
  ///The cost of a pirate
  cout<<"PirateCost\t"<<pirateCost()<<endl;
  ///The cost of a ship
  cout<<"ShipCost\t"<<shipCost()<<endl;
  cout<<"PortCost\t"<<portCost()<<endl;
  cout<<"boardX\t"<<mapSize()<<endl;
  cout<<"baordY\t"<<mapSize()<<endl;
  cout<<"--Object counts--"<<endl;
  cout<<"Pirates : "<<pirates.size()<<endl;
  displayPirates();
  cout<<"Ports   : "<<ports.size()<<endl;
  displayPorts();
  cout<<"Ships   : "<<ships.size()<<endl;
  displayShips();
  cout<<"Tiles   : "<<tiles.size()<<endl;
  displayTiles();
  cout<<"Treasure: "<<treasures.size()<<endl;
//  displayTreasure();
}

//This function is run once, after your last turn.
void AI::end()
{
  //cout<<"End Called"<<endl;
  //objectCheck();
}
