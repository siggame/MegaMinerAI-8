// -*-c++-*-

#ifndef SHIP_H
#define SHIP_H

#include <iostream>
#include "structures.h"

#include "Unit.h"
class Unit;

///A generic ship
class Ship : public Unit {
  public:
  Ship(_Ship* ptr = NULL);

  // Accessors
  ///Unique Identifier
  int id();
  ///The X position of the top left corner of this object.  X is horizontal
  int x();
  ///The Y position of the top left corner of this object.  Y is vertical
  int y();
  ///The owner of the unit
  int owner();
  ///health of the unit
  int health();
  ///attacking strength of the unit
  int strength();

  // Actions
  ///Move the unit to the designated X and Y coordinates
  int move(int x, int y);
  ///Allows a unit to display a message to the screen.
  int talk(char* message);
  ///Attempt to attack the given unit
  int attack(Unit& Target);

  // Properties


  friend std::ostream& operator<<(std::ostream& stream, Ship ob);
};

#endif

