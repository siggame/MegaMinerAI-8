// -*-c++-*-

#ifndef TILE_H
#define TILE_H

#include <iostream>
#include "structures.h"

#include "Mappable.h"

///Represents a single space on the map, can be owned by either player, neither player, or be a wall
class Tile : public Mappable {
  public:
  Tile(_Tile* ptr = NULL);

  // Accessors
  ///Unique Identifier
  int id();
  ///The x coordinate
  int x();
  ///The y cooridnate
  int y();
  ///who owns this tile: 0-First Player, 1-Second Player, 2-Not Owned, 3-Blocked
  int owner();

  // Actions

  // Properties


  friend std::ostream& operator<<(std::ostream& stream, Tile ob);
};

#endif

