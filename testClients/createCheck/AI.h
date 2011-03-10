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
const int yoff[] = {0, 1, 0, -1};
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
};

#endif
