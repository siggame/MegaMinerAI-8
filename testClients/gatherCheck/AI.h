#ifndef AI_H
#define AI_H

#include "BaseAI.h"
#include <iostream>
#include <algorithm>
#include <utility>
#include <limits.h>
#include <list>
#include <map>
#include <cmath>
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
  vector<Treasure*> booty;
  Ship* operator->(){return ship;}
  
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
  void displayPirates();
  template <class T>
  void sortNearest(int x, int y, list<T>& toSort, vector<MoveHelper<T> >& indexed, int type);
  template <class T>
  void sortNearest(list<T>& toSort,int x, int y, vector<MoveHelper<T> >& indexed, int type);
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
template <class T>
void AI::sortNearest(list<T>& toSort,int x, int y, vector<MoveHelper<T> >& indexed, int type)
{
  indexed.clear();
  for(typename list<T>::iterator it=toSort.begin();it!=toSort.end();it++)
  {
    MoveHelper<T> move;
    move.it = it;
    move.path = getPath((*it)->x(),(*it)->y(),x,y,type);
    if(move.path.size()!=0)
    {
      indexed.push_back(move);
    }
  }
  sort(indexed.begin(),indexed.end());
}
/*
template <class T>
void AI::sortNearest(int x, int y, vector<T>& toSort, vector<MoveHelper<T> >& indexed, int type)
{
  indexed.clear();
  for(typename vector<T>::iterator it=toSort.begin();it!=toSort.end();it++)
  {
    MoveHelper<T> move;
    //TODO Fix this
//    move.it = it;
    move.path = getPath(x,y,(*it).x(),(*it).y(),type);
    if(move.path.size()!=0)
    {
      indexed.push_back(move);
    }
  }
  sort(indexed.begin(),indexed.end());
}
*/
template <class T, class U>
bool samePos(T& first, U& second)
{
  return first.x()==second.x() and first.y()==second.y();
}

template <class T>
int lowestLiving(vector<T>& units)
{
  size_t choose=0;
  for(size_t i=1;i<units.size();i++)
  {
    if(units[i]->health() < units[choose]->health() && units[i]->health() > 0)
    {
      choose = i;
    }
  }
  return choose;
}

#endif
