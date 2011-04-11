#ifndef AI_H
#define AI_H

#include "BaseAI.h"
#include <iostream>
#include <algorithm>
#include <utility>
#include <limits.h>
#include <list>
#include <map>
using std::cout;
using std::endl;
using std::vector;
using namespace std;

template <class T>
struct MoveHelper
{
  MoveHelper(){}
  typename list<T>::iterator it;
  vector<Tile*> path;
  size_t length() const {return (path.size()==0)?INT_MAX:path.size();}
  friend bool operator<(const MoveHelper<T>& lhs, const MoveHelper<T>& rhs){return lhs.length() < rhs.length();}

};

struct Crew
{
  Ship* ship;
  vector<Pirate*> mates;
};

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
  void displayShips();
  template <class T>
  void sortNearest(int x, int y, list<T>& toSort, vector<MoveHelper<T> >& indexed, int type);
};

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

#endif
