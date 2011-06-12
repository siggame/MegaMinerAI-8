#include "AI.h"
#include "util.h"
#include <cmath>
AI::AI(Connection* conn) : BaseAI(conn) {}


//NOTE: You must change the return value of this to the username you team sets on MegaMinerAI.com
const char* AI::username()
{
  return "Shell AI";
}

//NOTE: You must change the return value of this to the password you team sets on MegaMinerAI.com
const char* AI::password()
{
  return "friday";
}

//This function is run once, before your first turn.
void AI::init()
{
  srand(time(NULL));
}

struct Location
{
  int x;
  int y;
};

bool noMoves = false;

vector<Location> dropSpots;

//This function is called each time it is your turn.
//Return true to end your turn, return false to ask the server for updated information.
bool AI::run()
{
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
  
  //ports[i].id()
    ///Unique Identifier

  //ports[i].x()
    ///The X position of this object.  X is horizontal, with 0,0 as the top left corner

  //ports[i].y()
    ///The Y position of this object.  Y is vertical, with 0,0 as the top left corner

  //ports[i].owner()
    ///The owner of the port
    
  //ports[i].createPirate()
    ///creates a pirate at the calling port
      
  //ports[i].createShip()
    ///creates a ship at the calling port
  ///////////////////////////////////////////////////////////////////
  
    ///////////////////////////////////////////////////////////////////
  //Pirate/Ship Functions:
  
  //pirates[i].id() / ships[i].id()
    ///Unique Identifier
    
  //pirates[i].x() / ships[i].x()
    ///The X position of this object.  X is horizontal, with 0,0 as the top left corner

  //pirates[i].y() / ships[i].y()
    ///The Y position of this object.  Y is vertical, with 0,0 as the top left corner

  //pirates[i].owner() / ships[i].owner()
    ///The owner of the unit

  //pirates[i].health() / ships[i].health()
    ///health of the unit

  //pirates[i].strength() / ships[i].strength()
    ///attacking strength of the unit

  //pirates[i].movesLeft() / ships[i].movesLeft()
    ///Attacks left this turn for the unit

  //pirates[i]/attacksLeft() / ships[i].attacksLeft()
    ///Moves left this turn for the unit

  //pirates[i].gold() / ships[i].gold()
    ///Amoutn of gold the unit is carrying
    
  //pirates[i].attack( Pirate target) / ships[i].attacks(Ship target)
    ///Attacks the passed in unit if possible
      
  //pirates[i].move(int x,int y) / ships[i].move(int x, int y)
    ///Moves to the passed in location if possible
    
  //pirates[i].createPort() (ONLY FOR PIRATES)
    ///Creates a port at the pirate's current location if possible 
    
  //pirates[i].pickupTreasure(int goldAmount) (ONLY FOR PIRATES)
    ///Picks up gold from the ground or from a port
  
  //pirates[i].dropTreasure(int goldAmount) (ONLY FOR PIRATES)
    ///Pirate drops its gold
  ///////////////////////////////////////////////////////////////////
  
  ///////////////////////////////////////////////////////////////////
  //Tile Functions:
  
  //tiles[i].id()
    ///Unique Identifier

  //tiles[i].x()
    ///The X position of this object.  X is horizontal, with 0,0 as the top left corner

  //tiles[i].y()
    ///The Y position of this object.  Y is vertical, with 0,0 as the top left corner

  //tiles[i].type()
    ///land = 0, water = 1
  ///////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////
  //Treasure Functions:
  
  //treasures[i].id()
    ///Unique Identifier

  //treasures[i].x()
    ///The X position of this object.  X is horizontal, with 0,0 as the top left corner

  //treasures[i].y()
    ///The Y position of this object.  Y is vertical, with 0,0 as the top left corner
  ///////////////////////////////////////////////////////////////////
  
  ///////////////////////////////////////////////////////////////////
  //Additional Functionality:

  //playerID()
    ///Can be used to identify what player you are.

  //PirateCost()
    ///Constant cost of a pirate unit

  //ShipCost()
    ///Constant cost of a ship unit

  //PortCost()
    ///Constant cost of a port

  //boardX()
    ///The max length of the board's X

  //boardY()
    ///The max length of the board's Y

  //getPath(int startX, int startY, int endX, int endY, int tileType) 
    ///Returns a vector of moves from the passed in start location to passed in end location over specified Tile type
    ///0 = Land, 1 = Water. 
    ///Example code provided in the snipets below
  ///////////////////////////////////////////////////////////////////
  if(turnNumber() == 0 || turnNumber() == 1)
  {
    for(int i = 0; i < pirates.size(); i++)
    {
      if(pirates[i].owner() == playerID())
      {
        pirates[i].pickupTreasure(50);
      }
    }
  }
  
  if(noMoves == false)
  {
    for(int i = 0; i<pirates.size();i++)
    {
      if(pirates[i].owner() == playerID())
      {
        closestEmptyTile(pirates[i]);
      }
    }
  } 
  if(turnNumber() == 375 || turnNumber() == 376)
  {
    for(int i = 0; i < ports.size(); i++)
    {
      if( ports[i].owner() == playerID())
      {
        for(int j = 0; j < 5; j++)
        {
          ports[i].createPirate();
        }
      }
    }
  }
  else if(noMoves == true && turnNumber() > 400 && dropSpots.size() > 0)
  {
    for(int i = 0; i<pirates.size();i++)
    {
      if(pirates[i].owner() == playerID())
      {
        collect(pirates[i]);
      }
    }
  }   
  else if(turnNumber() > 400 && dropSpots.size() == 0)
  {
    for(int i = 0; i<pirates.size();i++)
    {
      if(pirates[i].owner() == playerID())
      {
        deposit(pirates[i]);
      }
    } 
  }
  
 /* 
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
  }*/
  
  return true;
}

//This function is run once, after your last turn.
void AI::end(){}

int AI::distance(int startX, int startY, int endX, int endY)
{
  int distance = 0;
  distance = abs(startX - endX) + abs(startY - endY);
  return distance;
}

Tile AI::closestEmptyTile(Pirate pirate)
{
  Tile closestEmptyTile = tiles[0];
  int closestDistance = 1600;
  vector<Tile*> path; 
  if(pirate.gold() > 0)
  {
    for(int j = 0; j < tiles.size(); j++)
    {
      if(distance(pirate.x(),pirate.y(), tiles[j].x(),tiles[j].y()) < closestDistance)
      {
        if(tiles[j].type() == 0)
        {
          bool treasure = false;
          bool notPort = true;
          bool takenPath = false;
          for(int k = 0; k < treasures.size(); k++)
          {          
            if(treasures[k].x() == tiles[j].x() && treasures[k].y() == tiles[j].y())
            {
              treasure = true;
            }
          }
          for(int k = 0; k < ports.size(); k++)
          {          
            if(ports[k].x() == tiles[j].x() && ports[k].y() == tiles[j].y())
            {
              notPort = false;
            }
          }
          for(int k = 0; k < dropSpots.size();k++)
          {
            if(dropSpots[k].x == tiles[j].x() && dropSpots[k].y == tiles[j].y())
            {
              takenPath = true;
            }
          }
          if(treasure == false && notPort == true && takenPath == false)
          {
            Tile tempTile = tiles[j];
            path = getPath(pirate.x(),pirate.y(),tempTile.x(),tempTile.y(),0);
            bool blocked = false;
            for(int i = 0; i < path.size(); i++)
            {
              for(int l = 0; l < ports.size(); l++)
              {
                if(path[i]->x() == ports[l].x() && path[i]->y() == ports[l].y())
                {
                  blocked = true;
                }
              }
            }
            if(blocked == false)
            {
              closestDistance = distance(pirate.x(),pirate.y(), tiles[j].x(),tiles[j].y());
              closestEmptyTile = tiles[j];    
            }            
          }
        }
      }
    }
    if(path.size() > 0)
    {
      for(int step = 0; step < path.size() && pirate.movesLeft() > 0;step++)
      {
        pirate.move(path[step]->x(),path[step]->y());
        pirate.dropTreasure(1);
        Location temp;
        temp.x = path[step]->x();
        temp.y = path[step]->y();
        dropSpots.push_back(temp);
      }   
    }
    else
    {
      for(int i = 0; i < pirates.size();i++)
      {
        if(pirates[i].id() == pirate.id())
        {
          pirates[i].attack(pirates[i]);
        }
      }
      noMoves = true;
    }
  }
  else
  {
    for(int i = 0; i < pirates.size();i++)
    {
      if(pirates[i].owner() == playerID())
      {
        pirates[i].attack(pirates[i]);
      }
    }
    noMoves = true;
  }
  return closestEmptyTile;
}





void AI::collect(Pirate pirate)
{
  int bestSpot = 0;
  int amount = 0;
  vector<Location> newDropSpots;
  bool treasureExists = false;
  for(int i = 0; i < dropSpots.size(); i++)
  {
    if(distance(pirate.x(),pirate.y(),dropSpots[i].x,dropSpots[i].y) < distance(pirate.x(),pirate.y(),dropSpots[bestSpot].x,dropSpots[bestSpot].y))  
    {
      bestSpot = i;
    }
  }
  if(pirate.x() == dropSpots[bestSpot].x && pirate.y() == dropSpots[bestSpot].y)
  {
    for(int i = 0; i < treasures.size(); i++)
    {
      if( treasures[i].x() == pirate.x() && treasures[i].y() == pirate.y())
      {
        amount = treasures[i].gold();
        treasureExists = true;
      }
    }
    if(treasureExists == true)
    {
      pirate.pickupTreasure(amount);
      for(int i = 0; i < dropSpots.size();i++)
      {
        if(dropSpots[i].x == dropSpots[bestSpot].x && dropSpots[i].y == dropSpots[bestSpot].y)
        {
       
        }
        else
        {
          newDropSpots.push_back(dropSpots[i]);
        }
      }
      dropSpots = newDropSpots;
    }
    for(int i = 0; i < dropSpots.size(); i++)
    {
      if(distance(pirate.x(),pirate.y(),dropSpots[i].x,dropSpots[i].y) < distance(pirate.x(),pirate.y(),dropSpots[bestSpot].x,dropSpots[bestSpot].y))  
      {
        bestSpot = i;
      }
    }
    vector<Tile*> path = getPath(pirate.x(),pirate.y(),dropSpots[bestSpot].x,dropSpots[bestSpot].y,0); 
    for(int step = 0; step < path.size() && pirate.movesLeft() > 0;step++)
    {
      pirate.move(path[step]->x(),path[step]->y());
    }  
  }
  else
  {
    vector<Tile*> path = getPath(pirate.x(),pirate.y(),dropSpots[bestSpot].x,dropSpots[bestSpot].y,0); 
    for(int step = 0; step < path.size() && pirate.movesLeft() > 0;step++)
    {
      pirate.move(path[step]->x(),path[step]->y());
    }   
    for(int i = 0; i < treasures.size(); i++)
    {
      if( treasures[i].x() == pirate.x() && treasures[i].y() == pirate.y())
      {
        treasureExists = true;
        amount = treasures[i].gold();
      }
    }
    if(treasureExists == true)
    {
      pirate.pickupTreasure(amount);
      for(int i = 0; i < dropSpots.size();i++)
      {
        if(dropSpots[i].x == dropSpots[bestSpot].x && dropSpots[i].y == dropSpots[bestSpot].y)
        {
          
        }
        else
        {
          newDropSpots.push_back(dropSpots[i]);
        }
      }
      dropSpots = newDropSpots; 
    }    
  }
}

void AI::deposit(Pirate pirate)
{
  Location homePort;
  Tile destination;
  for(int i = 0; i < ports.size(); i++)
  {
    if(ports[i].owner() == playerID())
    {
      homePort.x = ports[i].x();
      homePort.y = ports[i].y();
    }
  }
  if(homePort.x == pirate.x() && homePort.y == pirate.y())
  {
    pirate.dropTreasure(pirate.gold());
    for(int i = 0; i < pirates.size();i++)
    {
      if(pirates[i].id() == pirate.id())
      {
        pirates[i].attack(pirates[i]);
      }
    }
  }
  else
  {
    vector<Tile*> path = getPath(pirate.x(),pirate.y(),homePort.x,homePort.y,0);
    for(int step = 0; step < path.size() && pirate.movesLeft() > 0;step++)
    {
      for(int i = 0; i < ports.size(); i++)
      {
        if(ports[i].x() == path[step]->x() && ports[i].y() == path[step]->y())
        {
          pirate.move(pirate.x() + rand()%1, pirate.y());
        }
        else
        {
          pirate.move(path[step]->x(),path[step]->y());
        }
      }
    }  
  }
}

