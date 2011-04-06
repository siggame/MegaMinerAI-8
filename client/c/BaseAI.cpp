//Copyright (C) 2009 - Missouri S&T ACM AI Team
//Please do not modify this file while building your AI
//See AI.h & AI.cpp for that

#include "BaseAI.h"
#include "game.h"

int BaseAI::turnNumber()
{
  return getTurnNumber(c);
}
int BaseAI::playerID()
{
  return getPlayerID(c);
}
int BaseAI::gameNumber()
{
  return getGameNumber(c);
}
int BaseAI::pirateCost()
{
  return getPirateCost(c);
}
int BaseAI::shipCost()
{
  return getShipCost(c);
}
int BaseAI::portCost()
{
  return getPortCost(c);
}
int BaseAI::mapSize()
{
  return getMapSize(c);
}

bool BaseAI::startTurn()
{
  static bool initialized = false;
  int count = 0;
  count = getPirateCount(c);
  pirates.clear();
  pirates.resize(count);
  for(int i = 0; i < count; i++)
  {
    pirates[i] = Pirate(getPirate(c, i));
  }

  count = getPlayerCount(c);
  players.clear();
  players.resize(count);
  for(int i = 0; i < count; i++)
  {
    players[i] = Player(getPlayer(c, i));
  }

  count = getPortCount(c);
  ports.clear();
  ports.resize(count);
  for(int i = 0; i < count; i++)
  {
    ports[i] = Port(getPort(c, i));
  }

  count = getShipCount(c);
  ships.clear();
  ships.resize(count);
  for(int i = 0; i < count; i++)
  {
    ships[i] = Ship(getShip(c, i));
  }

  count = getTileCount(c);
  tiles.clear();
  tiles.resize(count);
  for(int i = 0; i < count; i++)
  {
    tiles[i] = Tile(getTile(c, i));
  }

  count = getTreasureCount(c);
  treasures.clear();
  treasures.resize(count);
  for(int i = 0; i < count; i++)
  {
    treasures[i] = Treasure(getTreasure(c, i));
  }

  if(!initialized)
  {
    initialized = true;
    init();
  }
  return run();
}

BaseAI::BaseAI(Connection* conn) : c(conn) {}
BaseAI::~BaseAI() {}
