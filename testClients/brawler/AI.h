#ifndef AI_H
#define AI_H

#include "BaseAI.h"
#include "BRAWLER.h"
#include <iostream>
#include <algorithm>
#include <utility>
#include <limits.h>
using std::cout;
using std::endl;
using std::vector;
//*
template <class T>
struct MoveHelper
{
  MoveHelper():goal(NULL){}
  T* goal;
  vector<Tile*> path;
  size_t length() const {return (path.size()==0)?INT_MAX:path.size();}
  friend bool operator<(const MoveHelper<T>& lhs, const MoveHelper<T>& rhs){return lhs.length() < rhs.length();}

};
//*/
//enum GeneName{GENE_NAME_SIZE};
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
  void objectCheck();
  void displayPirates();
  void displayPorts();
  void displayShips();
  void displayTreasure();
  void displayTiles();
  BRAWLER weights;
  string database;
  template <class T>
  void sortNearest(int x, int y, vector<T>& list, vector<MoveHelper<T> >& indexed, int type);
};
//*

template <class T>
void AI::sortNearest(int x, int y, vector<T>& list, vector<MoveHelper<T> >& indexed, int type)
{
  indexed.clear();
  for(size_t i=0;i<list.size();i++)
  {
    MoveHelper<T> move;
    move.goal = &list[i];
    move.path = getPath(x,y,list[i].x(),list[i].y(),type);
    if(move.path.size()!=0)
    {
      indexed.push_back(move);
    }
    //indexed[i] = pair<int,T*>(abs(x-list[i].x()) + abs(y-list[i].y()),&(list[i]));
  }
  sort(indexed.begin(),indexed.end());
}
//*/
#endif
