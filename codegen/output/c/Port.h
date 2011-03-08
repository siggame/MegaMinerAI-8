// -*-c++-*-

#ifndef PORT_H
#define PORT_H

#include <iostream>
#include "structures.h"

#include "Mappable.h"

///A generic port
class Port : public Mappable {
  public:
  Port(_Port* ptr = NULL);

  // Accessors
  ///Unique Identifier
  int id();
  ///The X position of the top left corner of this object.  X is horizontal
  int x();
  ///The Y position of the top left corner of this object.  Y is vertical
  int y();
  ///The ownder of the port
  int owner();

  // Actions
  ///Creates a Pirate at the calling Port
  int createPirate();
  ///Creates a Ship at the calling Port
  int createShip();

  // Properties


  friend std::ostream& operator<<(std::ostream& stream, Port ob);
};

#endif

