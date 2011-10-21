// -*-c++-*-

#ifndef VIRUS_H
#define VIRUS_H

#include <iostream>
#include "structures.h"

#include "Mappable.h"

///Stores the information about a virus
class Virus : public Mappable {
  public:
  Virus(_Virus* ptr = NULL);

  // Accessors
  ///Unique Identifier
  int id();
  ///The x coordinate
  int x();
  ///The y cooridnate
  int y();
  ///The owner of this Virus
  int owner();
  ///The Virus's level
  int level();
  ///The number of times this virus can still move this turn
  int movesLeft();

  // Actions
  ///Moves a unit to the given (x,y) position
  int move(int x, int y);
  ///Allows a Virus to display a message to the screen.
  int talk(char* message);

  // Properties


  friend std::ostream& operator<<(std::ostream& stream, Virus ob);
};

#endif

