#ifndef AI_H
#define AI_H

#include "BaseAI.h"
#include <iostream>
#include <algorithm>
#include <utility>
#include <list>
#include <map>
using namespace std;


struct target
{
  target():x(0),y(0),priority(0){};
  target(size_t X, size_t Y, size_t P ):x(X),y(Y),priority(P){};
  size_t x,y,priority;
//  friend bool operator<(const target& lhs, const target& rhs){return lhs.priority > lhs.priority;} 
};

template <class T>
bool lowHigh(const T& lhs, const T&rhs)
{
  return lhs.priority < rhs.priority;
}
template <class T>
bool highLow(const T& lhs, const T&rhs)
{
  return lhs.priority > rhs.priority;
}
template <class T, class U>
bool samePos(T& first, U& second)
{
  return first.x()==second.x() and first.y()==second.y();
}


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
void sortNearest(int x, int y, list<T>& toSort, int type);

};

template <class T>
void AI::sortNearest(int x, int y, list<T>& toSort, int type)
{
  for(typename list<T>::iterator it=toSort.begin();it!=toSort.end();it++)
  {
    (*it).priority = getPath(x,y,(*it).x,(*it).y,type).size();
    // if there is a path
    if((*it).priority==0)
    {
      toSort.erase(it);
      it--;
    }
  }
  toSort.sort(lowHigh<target>);
}


#endif
