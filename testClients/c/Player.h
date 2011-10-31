// -*-c++-*-

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "structures.h"


///Stores information about a player in the game
class Player {
  public:
  void* ptr;
  Player(_Player* ptr = NULL);

  // Accessors
  ///Unique Identifier
  int id();
  ///Player's Name
  char* playerName();
  ///Player's points, one with more at end of game wins
  int byteDollars();
  ///Player's machine cycles, used to create new Virus's
  int cycles();
  ///The amount of time this player has before timing out
  int time();

  // Actions
  ///Allows a player to display a message to the screen.
  int talk(char* message);

  // Properties


  friend std::ostream& operator<<(std::ostream& stream, Player ob);
};

#endif

