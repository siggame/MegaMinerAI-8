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
void AI::init(){}

//This function is called each time it is your turn.
//Return true to end your turn, return false to ask the server for updated information.
bool AI::run()
{
  int myPirate=0,theirPirate=0,myTreasure=0;
  while(pirates[myPirate].owner() != playerID())myPirate++;
  while(pirates[theirPirate].owner() == playerID())theirPirate++;
  while(myTreasure<treasures.size() && treasures[myTreasure].pirateID() != pirates[myPirate].id())myTreasure++;
  if(myTreasure < treasures.size())
  {
    cout<<"I got a treasure: "<<treasures[myTreasure]<<endl;
  }
  pirates[myPirate].pickupTreasure(1);
  pirates[myPirate].dropTreasure(2);
  return true;
}

//This function is run once, after your last turn.
void AI::end(){}
