// -*-c++-*-

#include "Treasure.h"
#include "game.h"

#include "Pirate.h"

Treasure::Treasure(_Treasure* pointer)
{
    ptr = (void*) pointer;
}

int Treasure::id()
{
  return ((_Treasure*)ptr)->id;
}

int Treasure::x()
{
  return ((_Treasure*)ptr)->x;
}

int Treasure::y()
{
  return ((_Treasure*)ptr)->y;
}

_Pirate* Treasure::pirate()
{
  return ((_Treasure*)ptr)->pirate;
}




std::ostream& operator<<(std::ostream& stream,Treasure ob)
{
  stream << "id: " << ((_Treasure*)ob.ptr)->id  <<'\n';
  stream << "x: " << ((_Treasure*)ob.ptr)->x  <<'\n';
  stream << "y: " << ((_Treasure*)ob.ptr)->y  <<'\n';
  stream << "pirate: " << ((_Treasure*)ob.ptr)->pirate  <<'\n';
  return stream;
}
