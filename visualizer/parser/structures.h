//Copyright (C) 2009 - Missouri S&T ACM AI Team
//Please do not modify this file while building your AI
//See AI.h & AI.cpp for that
#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <iostream>
#include <vector>
#include <map>
#include <string>

const int MOVE = 0;

struct Move
{
  int id;
  int fromFile;
  int fromRank;
  int toFile;
  int toRank;
  int promoteType;

  friend std::ostream& operator<<(std::ostream& stream, Move obj);
};

struct Piece
{
  int id;
  int owner;
  int file;
  int rank;
  int hasMoved;
  int type;

  friend std::ostream& operator<<(std::ostream& stream, Piece obj);
};


struct Animation
{
  int type;
};

struct move : public Animation
{
  int fromFile;
  int fromRank;
  int toFile;
  int toRank;
  int promoteType;

  friend std::ostream& operator<<(std::ostream& stream, move obj);
};


struct GameState
{
  std::map<int,Move> moves;
  std::map<int,Piece> pieces;

  int turnNumber;
  int playerID;
  int gameNumber;
  int TurnsToStalemate;
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
