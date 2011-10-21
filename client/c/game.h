//Copyright (C) 2009 - Missouri S&T ACM AI Team
//Please do not modify this file while building your AI
//See AI.h & AI.cpp for that
#ifndef GAME_H
#define GAME_H

#include "network.h"
#include "structures.h"

#ifdef _WIN32
#define DLLEXPORT extern "C" __declspec(dllexport)

#ifdef ENABLE_THREADS
#include "pthread.h"
#endif

#else
#define DLLEXPORT

#ifdef ENABLE_THREADS
#include <pthread.h>
#endif

#endif

struct Connection
{
  int socket;
  
  #ifdef ENABLE_THREADS
  pthread_mutex_t mutex;
  #endif
  
  int turnNumber;
  int playerID;
  int gameNumber;
  int baseCost;
  float scaleCost;
  int width;
  int height;

  _Base* Bases;
  int BaseCount;
  _Player* Players;
  int PlayerCount;
  _Tile* Tiles;
  int TileCount;
  _Virus* Viruses;
  int VirusCount;
};

#ifdef __cplusplus
extern "C"
{
#endif
  DLLEXPORT Connection* createConnection();
  DLLEXPORT void destroyConnection(Connection* c);
  DLLEXPORT int serverConnect(Connection* c, const char* host, const char* port);

  DLLEXPORT int serverLogin(Connection* c, const char* username, const char* password);
  DLLEXPORT int createGame(Connection* c);
  DLLEXPORT int joinGame(Connection* c, int id);

  DLLEXPORT void endTurn(Connection* c);
  DLLEXPORT void getStatus(Connection* c);


//commands

  ///Creates a Virus on the base with certain level.
  DLLEXPORT int baseSpawn(_Base* object, int Level);
  ///Allows a player to display a message to the screen.
  DLLEXPORT int playerTalk(_Player* object, char* message);
  ///Moves a unit to the given (x,y) position
  DLLEXPORT int virusMove(_Virus* object, int x, int y);
  ///Allows a Virus to display a message to the screen.
  DLLEXPORT int virusTalk(_Virus* object, char* message);

//derived properties



//accessors

DLLEXPORT int getTurnNumber(Connection* c);
DLLEXPORT int getPlayerID(Connection* c);
DLLEXPORT int getGameNumber(Connection* c);
DLLEXPORT int getBaseCost(Connection* c);
DLLEXPORT float getScaleCost(Connection* c);
DLLEXPORT int getWidth(Connection* c);
DLLEXPORT int getHeight(Connection* c);

DLLEXPORT _Base* getBase(Connection* c, int num);
DLLEXPORT int getBaseCount(Connection* c);

DLLEXPORT _Player* getPlayer(Connection* c, int num);
DLLEXPORT int getPlayerCount(Connection* c);

DLLEXPORT _Tile* getTile(Connection* c, int num);
DLLEXPORT int getTileCount(Connection* c);

DLLEXPORT _Virus* getVirus(Connection* c, int num);
DLLEXPORT int getVirusCount(Connection* c);



  DLLEXPORT int networkLoop(Connection* c);
#ifdef __cplusplus
}
#endif

#endif
