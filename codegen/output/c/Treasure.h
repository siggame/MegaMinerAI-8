// -*-c++-*-

#ifndef TREASURE_H
#define TREASURE_H

#include <iostream>
#include "structures.h"

#include "Mappable.h"
class Pirate;

///A treasure
class Treasure : public Mappable {
  public:
  Treasure(_Treasure* ptr = NULL);

  // Accessors
  ///Unique Identifier
  int id();
  ///The X position of the top left corner of this object.  X is horizontal
  int x();
  ///The Y position of the top left corner of this object.  Y is vertical
  int y();
  ///The pirate carrying this treasure
  _Pirate* pirate();

  // Actions

  // Properties


  friend std::ostream& operator<<(std::ostream& stream, Treasure ob);
};

#endif

