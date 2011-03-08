//Copyright (C) 2009 - Missouri S&T ACM AI Team
//Please do not modify this file while building your AI
//See AI.h & AI.cpp for that
#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <iostream>
#include <vector>
#include <map>
#include <string>


struct Mappable
{
  int id;
  int x;
  int y;

  friend std::ostream& operator<<(std::ostream& stream, Mappable obj);
};

struct Unit: public Mappable 
{
  int owner;
  int health;
  int strength;

  friend std::ostream& operator<<(std::ostream& stream, Unit obj);
};

struct Pirate: public Unit 
{

  friend std::ostream& operator<<(std::ostream& stream, Pirate obj);
};

struct Port: public Mappable 
{
  int owner;

  friend std::ostream& operator<<(std::ostream& stream, Port obj);
};

struct Ship: public Unit 
{

  friend std::ostream& operator<<(std::ostream& stream, Ship obj);
};

struct Tile: public Mappable 
{
  int type;

  friend std::ostream& operator<<(std::ostream& stream, Tile obj);
};

struct Treasure: public Mappable 
{
  int pirate;

  friend std::ostream& operator<<(std::ostream& stream, Treasure obj);
};


struct Animation
{
  int type;
};


struct GameState
{
  std::map<int,Mappable> mappables;
  std::map<int,Unit> units;
  std::map<int,Pirate> pirates;
  std::map<int,Port> ports;
  std::map<int,Ship> ships;
  std::map<int,Tile> tiles;
  std::map<int,Treasure> treasures;

  int turnNumber;
  int playerID;
  int gameNumber;
  int player0Time;
  int player1Time;

  std::vector<Animation*> animations;
  friend std::ostream& operator<<(std::ostream& stream, GameState obj);
};

struct Game
{
  std::vector<GameState> states;
  std::string players[2];
  int winner;
	std::string winReason;

  Game();
};

#endif
