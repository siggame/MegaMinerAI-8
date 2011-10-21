//Copyright (C) 2009 - Missouri S&T ACM AI Team
//Please do not modify this file while building your AI
//See AI.h & AI.cpp for that
#ifndef STRUCTURES_H
#define STRUCTURES_H

struct Connection;
struct _Mappable;
struct _Base;
struct _Player;
struct _Tile;
struct _Virus;


struct _Mappable
{
  Connection* _c;
  int id;
  int x;
  int y;
};
struct _Base
{
  Connection* _c;
  int id;
  int x;
  int y;
  int owner;
  int spawnsLeft;
};
struct _Player
{
  Connection* _c;
  int id;
  char* playerName;
  int byteDollars;
  int cycles;
};
struct _Tile
{
  Connection* _c;
  int id;
  int x;
  int y;
  int owner;
};
struct _Virus
{
  Connection* _c;
  int id;
  int x;
  int y;
  int owner;
  int level;
  int movesLeft;
};

#endif
