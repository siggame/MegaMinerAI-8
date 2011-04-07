#ifndef AI_H
#define AI_H

#include "BaseAI.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
using std::cout;
using std::endl;
using std::vector;

const int xoff[] = {0, 1, 0, -1};
const int yoff[] = {1, 0, -1, 0};
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
  bool shipAt(int x, int y);
  vector<vector<bool> > land;
  vector<vector<int> > port;
  vector<vector<bool> > map;

};

#endif