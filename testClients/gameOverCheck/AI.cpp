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
  // TO CHANGE WIN CONDIITON, CHANGE THIS!
  int keepPirates=1;
  int keepShips=0;
  int keepGold=0;
  int countPirates=0,countShips=0,countGold=0;
  
  // find your port
  int myPort=0;
  while(ports[myPort].owner() != playerID())myPort++;

  // spend money until you are down to the desired gold
  while(players[playerID()].gold()- countGold > keepGold)
  {
    cout<<"Buying a pirate"<<endl;
    ports[myPort].createPirate();
    countGold+=pirateCost();
  }
  for(size_t i=0;i<pirates.size();i++)
  {
    if(pirates[i].owner()==playerID())
    {
      if(countPirates < keepPirates)
      {
        countPirates++;
      }
      else
      {
        cout<<"Killing a pirate"<<endl;
        pirates[i].attack(pirates[i]);
      }
    }
  }
  for(size_t i=0;i<ships.size();i++)
  {
    if(ships[i].owner()==playerID())
    {
      if(countShips < keepShips)
      {
        countShips++;
      }
      else
      {
        cout<<"Ship attacking itself"<<endl;
        ships[i].attack(ships[i]);
      }
    }
  }
  cout<<"Should have: "<<countPirates<<" "<<countShips<<" "<<players[playerID()].gold()-countGold<<endl;
  return true;
}

//This function is run once, after your last turn.
void AI::end(){}
