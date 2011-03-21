#ifndef AI_H
#define AI_H

#include "BaseAI.h"
#include "BRAWLER.h"
#include <iostream>
using std::cout;
using std::endl;
using std::vector;
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
};

#endif
