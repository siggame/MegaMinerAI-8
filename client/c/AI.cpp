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
void AI::init(){}

//This function is called each time it is your turn.
//Return true to end your turn, return false to ask the server for updated information.
bool AI::run()
{
  // loop through all of the bases
  for(int i=0;i<bases.size();i++)
  {
    // check if you own that base
    if(bases[i].owner() == playerID())
    {
      // check to see if you have enough cycles to spawn a level 0 virus
      if(baseCost() <= players[playerID()].cycles())
      {
        // spawn a level 0 virus at that base
        bases[i].spawn(0);
      }
    }
  }

  // loop through all of the viruses
  for(int i=0;i<viruses.size();i++)
  {
    // if you own that virus
    if(viruses[i].owner() == playerID())
    {
      // if the tile you want to move to is NOT a wall
      if(getTileAtLocation(viruses[i].x()+1, viruses[i].y()).owner() != 3)
      {
        // move the virus
        viruses[i].move(viruses[i].x()+1, viruses[i].y());
      }
    }
  }
  // End your turn
  return true;
}

//This function is run once, after your last turn.
void AI::end(){}
