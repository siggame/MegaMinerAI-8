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
  cout<<"Initializing"<<endl;
  srand(time(NULL));
}

//This function is called each time it is your turn.
//Return true to end your turn, return false to ask the server for updated information.
bool AI::run()
{
  cout<<"Turn: "<<turnNumber()<<" My ID: "<<playerID()<<" My Gold: "<<players[playerID()].gold()<<endl;  
  //////////////////////////////////////////////
  //Pre-Defined Data Structures : 
  //vector<Pirate> pirates
  //vector<Ship> ships
  //vector<Port> ports
  //vector<Tile> tiles
  //vector<Treasure> treasures
  ///////////////////////////////////////////// 
  //If you are a cs53 student and don't know what a vector is or how to use it
  //please find a Dev and we will help you! 
  /////////////////////////////////////////////////////////////////
  
  /////////////////////////////////////////////////////////////////
  //Port Functions:  
  
  ///Unique Identifier
  //ports[i].id()
  
  ///The X position of this object.  X is horizontal, with 0,0 as the top left corner
  //ports[i].x()
  
  ///The Y position of this object.  Y is vertical, with 0,0 as the top left corner
  //ports[i].y()
  
  ///The owner of the port
  //cports[i].owner()
  ///////////////////////////////////////////////////////////////////
  
    ///////////////////////////////////////////////////////////////////
  //Pirate/Ship Functions:
  
  ///Unique Identifier
  //pirates[i].id() / ships[i].id()
  
  ///The X position of this object.  X is horizontal, with 0,0 as the top left corner
  //pirates[i].x() / ships[i].x()
  
  ///The Y position of this object.  Y is vertical, with 0,0 as the top left corner
  //pirates[i].y() / ships[i].y()
  
  ///The owner of the unit
  //pirates[i].owner() / ships[i].owner()
  
  ///health of the unit
  //pirates[i].health() / ships[i].health()
  
  ///attacking strength of the unit
  //pirates[i].strength() / ships[i].strength()
  
  ///Attacks left this turn for the unit
  //pirates[i].movesLeft() / ships[i].movesLeft()
  
  ///Moves left this turn for the unit
  //pirates[i]/attacksLeft() / ships[i].attacksLeft()
  
  ///Amoutn of gold the unit is carrying
  //pirates[i].gold() / ships[i].gold()
  ///////////////////////////////////////////////////////////////////
  
  ///////////////////////////////////////////////////////////////////
  //Time Functions:
  
  ///Unique Identifier
  //tiles[i].id()
  
  ///The X position of this object.  X is horizontal, with 0,0 as the top left corner
  //tiles[i].x()
  
  ///The Y position of this object.  Y is vertical, with 0,0 as the top left corner
  //tiles[i].y()
  
  ///land = 0, water = 1
  //tiles[i].type()
  ///////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////
  //Treasure Functions:
  
  ///Unique Identifier
  //treasures[i].id()
  
  ///The X position of this object.  X is horizontal, with 0,0 as the top left corner
  //treasures[i].x()
  
  ///The Y position of this object.  Y is vertical, with 0,0 as the top left corner
  //treasures[i].y()
  ///////////////////////////////////////////////////////////////////
  
  ///////////////////////////////////////////////////////////////////
  //Additional Functionality:
  ///Can be used to identify what player you are.
  //playerID()
  
  ///Constant cost of a pirate unit
  //PirateCost()
  
  ///Constant cost of a ship unit
  //ShipCost()
  
  ///Constant cost of a port
  //PortCost()
  
  ///The max length of the board's X
  //boardX()
  
  ///The max length of the board's Y
  //boardY()
  
   ///Returns a vector of moves from the passed in start location to passed in end location over specified Tile type
   ///0 = Land, 1 = Water. 
   ///Example code provided in the snipets below
  //getPath(int startX, int startY, int endX, int endY, int timeType) 
  ///////////////////////////////////////////////////////////////////

  
  // if you have enough gold to buy a pirate
  if(pirateCost() < players[playerID()].gold())
  {
    // find a port that you own
    for(int p=0;p<ports.size();p++)
    {
      if(ports[p].owner()==playerID())
      {
        ports[p].createPirate();
        break;
      }
    }
  }
  
  // For each pirate in the world
  for(int i=0;i<pirates.size();i++)
  {
    // if I own the pirate
    if(pirates[i].owner()==playerID())
    {
      // select a random pirate from the list
      int target = rand()%pirates.size();
      // Does a naive path finding algorithm that only takes into account tile types, not other blocking problems
      // Takes a start x, start y, end x, end y, and a tile type you wish to path on (0 for land, 1 for water)
      vector<Tile*> path = getPath(pirates[i].x(),pirates[i].y(),pirates[target].x(),pirates[target].y(),0);
      
      // For all but the last step of the path, while I have steps, move
      for(int step = 0; step+1 < path.size() && pirates[i].movesLeft() > 0;step++)
      {
        pirates[i].move(path[step]->x(),path[step]->y());
      }
      
      // get the distance between the guys
      int distance = abs(pirates[i].x() + pirates[target].x()) + abs(pirates[i].y()-pirates[target].y());
      
      // If the distance is exactly 1 away and I don't own the guy
      if( distance == 1 && pirates[i].owner() != pirates[target].owner())
      {
        while(pirates[i].attacksLeft() > 0 )
        {
          // attack the target
          pirates[i].attack(pirates[target]);
        }
      }
    }
  }
  
  return true;
}

//This function is run once, after your last turn.
void AI::end(){}
