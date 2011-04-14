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

  // if you have enough gold to buy a pirate
  if(pirateCost() < players[playerID()].gold())
  {
    // find a port that you own
    for(size_t p=0;p<ports.size();p++)
    {
      if(ports[p].owner()==playerID())
      {
        ports[p].createPirate();
        break;
      }
    }
  }
  
  // For each pirate in the world
  for(size_t i=0;i<pirates.size();i++)
  {
    // if I own the pirate
    if(pirates[i].owner()==playerID())
    {
      // select a random pirate from the list
      int target = rand()%pirates.size();
      // Does a naive path finding algorithm that only takes into account tile types, not other blocking problems
      // Takes a start x, start y, end x, end y, and a tile type you wish to path on
      vector<Tile*> path = getPath(pirates[i].x(),pirates[i].y(),pirates[target].x(),pirates[target].y(),0);
      // for all but the last step of the path, while I have steps, move
      for(size_t step=0;step+1<path.size() && pirates[i].movesLeft()>0;step++)
      {
        pirates[i].move(path[step]->x(),path[step]->y());
      }
      // get the distance between the guys
      int distance = abs(pirates[i].x() + pirates[target].x()) + abs(pirates[i].y()+pirates[target].y());
      
      // If the distance is exactly 1 away and I don't own the guy
      if( distance ==1 && pirates[i].owner()!=pirates[target].owner())
      {
        while(pirates[i].movesLeft()>0)
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
