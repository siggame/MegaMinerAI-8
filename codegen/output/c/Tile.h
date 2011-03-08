// -*-c++-*-

#ifndef TILE_H
#define TILE_H

#include <iostream>
#include "structures.h"

#include "Mappable.h"

///A basic tile
class Tile : public Mappable {
  public:
  Tile(_Tile* ptr = NULL);

  // Accessors
  ///Unique Identifier
  int id();
  ///The X position of the top left corner of this object.  X is horizontal
  int x();
  ///The Y position of the top left corner of this object.  Y is vertical
  int y();
  ///land = 0, water = 1
  int type();

  // Actions

  // Properties


  friend std::ostream& operator<<(std::ostream& stream, Tile ob);
};

#endif

