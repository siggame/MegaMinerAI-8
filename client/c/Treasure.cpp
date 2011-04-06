// -*-c++-*-

#include "Treasure.h"
#include "game.h"


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

int Treasure::pirateID()
{
  return ((_Treasure*)ptr)->pirateID;
}

int Treasure::amount()
{
  return ((_Treasure*)ptr)->amount;
}




std::ostream& operator<<(std::ostream& stream,Treasure ob)
{
  stream << "id: " << ((_Treasure*)ob.ptr)->id  <<'\n';
  stream << "x: " << ((_Treasure*)ob.ptr)->x  <<'\n';
  stream << "y: " << ((_Treasure*)ob.ptr)->y  <<'\n';
  stream << "pirateID: " << ((_Treasure*)ob.ptr)->pirateID  <<'\n';
  stream << "amount: " << ((_Treasure*)ob.ptr)->amount  <<'\n';
  return stream;
}
