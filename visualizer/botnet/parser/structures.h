//Copyright (C) 2009 - Missouri S&T ACM AI Team
//Please do not modify this file while building your AI
//See AI.h & AI.cpp for that
#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "smartpointer.h"

const int COMBAT = 0;
const int COMBINE = 1;
const int CRASH = 2;
const int CREATE = 3;
const int MOVE = 4;
const int PLAYERTALK = 5;
const int RECYCLE = 6;

struct Mappable
{
  int id;
  int x;
  int y;

  friend std::ostream& operator<<(std::ostream& stream, Mappable obj);
};

struct Base: public Mappable 
{
  int owner;
  int spawnsLeft;

  friend std::ostream& operator<<(std::ostream& stream, Base obj);
};

struct Player
{
  int id;
  char* playerName;
  int byteDollars;
  int cycles;
  int time;

  friend std::ostream& operator<<(std::ostream& stream, Player obj);
};

struct Tile: public Mappable 
{
  int owner;

  friend std::ostream& operator<<(std::ostream& stream, Tile obj);
};

struct Virus: public Mappable 
{
  int owner;
  int level;
  int movesLeft;
  int living;

  friend std::ostream& operator<<(std::ostream& stream, Virus obj);
};


struct Animation
{
  int type;
};

struct Combat : public Animation
{
  int moving;
  int stationary;

  friend std::ostream& operator<<(std::ostream& stream, Combat obj);
};

struct Combine : public Animation
{
  int moving;
  int stationary;

  friend std::ostream& operator<<(std::ostream& stream, Combine obj);
};

struct Crash : public Animation
{
  int crashing;
  int dx;
  int dy;

  friend std::ostream& operator<<(std::ostream& stream, Crash obj);
};

struct Create : public Animation
{
  int creating;

  friend std::ostream& operator<<(std::ostream& stream, Create obj);
};

struct Move : public Animation
{
  int moving;
  int dx;
  int dy;

  friend std::ostream& operator<<(std::ostream& stream, Move obj);
};

struct PlayerTalk : public Animation
{
  int speaker;
  char* message;

  friend std::ostream& operator<<(std::ostream& stream, PlayerTalk obj);
};

struct Recycle : public Animation
{
  int recycling;
  int base;

  friend std::ostream& operator<<(std::ostream& stream, Recycle obj);
};


struct AnimOwner: public Animation
{
  int owner;
};

struct GameState
{
  std::map<int,Mappable> mappables;
  std::map<int,Base> bases;
  std::map<int,Player> players;
  std::map<int,Tile> tiles;
  std::map<int,Virus> viruses;

  int turnNumber;
  int playerID;
  int gameNumber;
  int baseCost;
  float scaleCost;
  int width;
  int height;

  std::map< int, std::vector< SmartPointer< Animation > > > animations;
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
