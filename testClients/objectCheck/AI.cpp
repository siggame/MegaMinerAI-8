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
  cout<<"Initialization called"<<endl;
  objectCheck();
}

//This function is called each time it is your turn.
//Return true to end your turn, return false to ask the server for updated information.
bool AI::run()
{
  cout<<"Starting turn: "<<turnNumber()<<endl;
  objectCheck();
  return true;
}

void AI::objectCheck()
{
  cout<<"--Object counts--"<<endl;
  cout<<"Pirates: "<<pirates.size()<<endl;
  cout<<"Ports  : "<<ports.size()<<endl;
  cout<<"Ships  : "<<ships.size()<<endl;
  cout<<"Tiles  : "<<tiles.size()<<endl;
  cout<<"Treasur: "<<treasures.size()<<endl;
}

//This function is run once, after your last turn.
void AI::end()
{
  cout<<"End Called"<<endl;
  objectCheck();
}
