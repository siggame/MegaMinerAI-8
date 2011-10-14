// -*-c++-*-

#ifndef BASE_H
#define BASE_H

#include <iostream>
#include "structures.h"

#include "Mappable.h"

///The information on the base
class Base : public Mappable {
  public:
  Base(_Base* ptr = NULL);

  // Accessors
  ///Unique Identifier
  int id();
  ///The x coordinate
  int x();
  ///The y cooridnate
  int y();
  ///Whose base this is, all your base are belong to who
  int owner();
  ///The number of viruses this base can still spawn this turn
  int spawnsLeft();

  // Actions
  ///Creates a Virus on the base with certain level.
  int spawn(int Level);

  // Properties


  friend std::ostream& operator<<(std::ostream& stream, Base ob);
};

#endif

