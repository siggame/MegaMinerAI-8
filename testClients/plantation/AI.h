#ifndef AI_H
#define AI_H
#include <list>
#include <iostream>
#include <algorithm>
#include <utility>
#include <cmath>
#include <cstdlib>

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
  vector<vector<size_t> > gold;
  vector<vector<bool> > land;
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

template <class T, class U>
bool at(T& first, list<U>& set)
{
  for(typename list<U>::iterator it=set.begin();it!=set.end();it++)
  {
    if(samePos(first,**it))
    {
      return true;
    }
  }
  return false;
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
