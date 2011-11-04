//Copyright (C) 2009 - Missouri S&T ACM AI Team
//Please do not modify this file while building your AI
//See AI.h & AI.cpp for that
#ifndef BASEAI_H
#define BASEAI_H

#include <vector>
#include <ctime>
#include "game.h"

#include "Mappable.h"
#include "Base.h"
#include "Player.h"
#include "Tile.h"
#include "Virus.h"

/// \brief A basic AI interface.

///This class implements most the code an AI would need to interface with the lower-level game code.
///AIs should extend this class to get a lot of boiler-plate code out of the way
///The provided AI class does just that.
class BaseAI
{
protected:
  Connection* c;
  std::vector<Base> bases;
  std::vector<Player> players;
  std::vector<Tile> tiles;
  std::vector<Virus> viruses;
public:
  ///How many turns it has been since the beginning of the game
  int turnNumber();
  ///Player Number; either 0 or 1 (0 is player 1, 1 is player 2)
  int playerID();
  ///What number game this is for the server
  int gameNumber();
  ///BaseCost used in the virus price formula
  int baseCost();
  ///Scalar used in the virus price formula
  float scaleCost();
  ///The width of the map (max X value)
  int width();
  ///The height of the map (max Y value)
  int height();
  ///Gets the tile at the specified location
  Tile& getTile(int x, int y);
  
  BaseAI(Connection* c);
  virtual ~BaseAI();
  ///
  ///Make this your username, which should be provided.
  virtual const char* username() = 0;
  ///
  ///Make this your password, which should be provided.
  virtual const char* password() = 0;
  ///
  ///This function is run once, before your first turn.
  virtual void init() = 0;
  ///
  ///This function is called each time it is your turn
  ///Return true to end your turn, return false to ask the server for updated information
  virtual bool run() = 0;
  ///
  ///This function is called after the last turn.
  virtual void end() = 0;


  bool startTurn();
};

#endif
