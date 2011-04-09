#ifndef AI_H
#define AI_H

#include "BaseAI.h"
#include "BRAWLER.h"
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
//*
template <class T>
struct MoveHelper
{
  MoveHelper(){}
  typename list<T>::iterator it;
  vector<Tile*> path;
  size_t length() const {return (path.size()==0)?INT_MAX:path.size();}
  friend bool operator<(const MoveHelper<T>& lhs, const MoveHelper<T>& rhs){return lhs.length() < rhs.length();}

};

// Consider adding what "type" of objectives
struct Objective
{
  Objective():X(0),Y(0),priority(0),needs(0),pToAttack(NULL){}
  Objective(int _X, int _Y):X(_X),Y(_Y),priority(0),needs(0),pToAttack(NULL){};
  Objective(int _X, int _Y,int P, int N):X(_X),Y(_Y),priority(P),needs(N),pToAttack(NULL){};
  int X, Y;
  int x(){return X;}
  int y(){return Y;}
  int priority, needs;
  vector<Pirate*> workers;
  Pirate* pToAttack;
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
  void sortNearest(int x, int y, list<T>& toSort, vector<MoveHelper<T> >& indexed, int type);
  
  void execute(Objective& obj);
};
//*

template <class T>
void AI::sortNearest(int x, int y, list<T>& toSort, vector<MoveHelper<T> >& indexed, int type)
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
//*/
#endif
