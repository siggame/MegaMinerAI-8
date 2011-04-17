#ifndef AI_H
#define AI_H
#include <list>
#include <iostream>
#include <algorithm>
#include <utility>
#include <cmath>
#include <cstdlib>
#include <set>
#include <list>
using namespace std;
#include "BaseAI.h"
template <class T>
struct MoveHelper
{
  MoveHelper(){}
  typename list<T>::iterator it;
  vector<Tile*> path;
  size_t length() const {return path.size();}
  friend bool operator<(const MoveHelper<T>& lhs, const MoveHelper<T>& rhs){return lhs.length() < rhs.length();}

};

enum PirateStates {CREW, SEED, GATHER, GOTOPORT, STARTSEED, P_SIZE};
enum ShipStates {HUNT, CARGO, TAXI, S_SIZE};

class AI;

typedef void (AI::*ShipJob)(Ship&);
typedef void (AI::*PirateJob)(Pirate&);

///The class implementing gameplay logic.
class AI: public BaseAI
{
public:
  AI(Connection* c);
  virtual const char* username();
  virtual const char* password();
  virtual void init();
  virtual bool run();
  virtual void end();
  template <class T>
  void sortNearest(int x, int y, list<T>& toSort, vector<MoveHelper<T> >& indexed, int type);
  
  vector<set<int> > pirateIdentify, shipIdentify;
  void crewCommand(Pirate& pirates);
  void seedCommand(Pirate& pirates);
  void gatherCommand(Pirate& pirates);
  void goToPortCommand(Pirate& pirate);
  void startSeedCommand(Pirate& pirate);
  
  void huntCommand(Ship& ship);
  void cargoCommand(Ship& ship);
  void taxiCommand(Ship& ship);

  template <class T>
  bool command(set<int>& s, T& actor, void (AI::*job)(T&));
  
  void giveJob(Pirate& pirate);
  void giveJob(Ship& ship);
  
  void stateSwitch(PirateStates from, PirateStates to, int id);
  void stateSwitch(ShipStates from, ShipStates to, int id);
  
  vector<vector<bool> > landable;
  vector<vector<size_t> > gold;
  void buildLandable();
  void buildEmpty();
  void buildHarvest();
  void buildMyPorts();
  
  //TODO Config numbers
  size_t seedMoney, gatheredEnough;
  
  list<Tile*> empty;
  list<Treasure*> harvest;
  list<Port*> myPorts;
};

const PirateJob pirateJobList[] = { &AI::crewCommand, &AI::seedCommand, &AI::gatherCommand, &AI::goToPortCommand, &AI::startSeedCommand };
const ShipJob shipJobList[] = { &AI::huntCommand, &AI::cargoCommand, &AI::taxiCommand };

template <class T>
bool AI::command(set<int>& s, T& actor, void (AI::*job)(T&))
{
  bool in;
  if(in = (s.find(actor.id()) != s.end()))
  {
    (this->*job)(actor);
  }
  return in;
}

template <class T>
void AI::sortNearest(int x, int y, list<T>& toSort, vector<MoveHelper<T> >& indexed, int type)
{
  indexed.clear();
  for(typename list<T>::iterator it=toSort.begin();it!=toSort.end();it++)
  {
    MoveHelper<T> move;
    move.it = it;
    move.path = getPath(x,y,(*it)->x(),(*it)->y(),type);
    if(move.path.size()!=0)
    {
      indexed.push_back(move);
    }
  }
  sort(indexed.begin(),indexed.end());
}

template <class T, class U>
bool samePos(T& first, U& second)
{
  return first.x()==second.x() and first.y()==second.y();
}

template <class T, class U>
bool inRange(T& first, U& second)
{
  return abs(first.x()-second.x())+abs(first.y()-second.y())==1;
}
#endif
