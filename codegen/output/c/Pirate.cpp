// -*-c++-*-

#include "Pirate.h"
#include "game.h"

#include "Unit.h"

Pirate::Pirate(_Pirate* pointer)
{
    ptr = (void*) pointer;
}

int Pirate::id()
{
  return ((_Pirate*)ptr)->id;
}

int Pirate::x()
{
  return ((_Pirate*)ptr)->x;
}

int Pirate::y()
{
  return ((_Pirate*)ptr)->y;
}

int Pirate::owner()
{
  return ((_Pirate*)ptr)->owner;
}

int Pirate::health()
{
  return ((_Pirate*)ptr)->health;
}

int Pirate::strength()
{
  return ((_Pirate*)ptr)->strength;
}


int Pirate::move(int x, int y)
{
  return pirateMove( (_Pirate*)ptr, x, y);
}

int Pirate::talk(char* message)
{
  return pirateTalk( (_Pirate*)ptr, message);
}

int Pirate::pickupTreasure(int amount)
{
  return piratePickupTreasure( (_Pirate*)ptr, amount);
}

int Pirate::dropTreasure(int amount)
{
  return pirateDropTreasure( (_Pirate*)ptr, amount);
}

int Pirate::attack(Unit& Target)
{
  return pirateAttack( (_Pirate*)ptr, (_Unit*) Target.ptr);
}



std::ostream& operator<<(std::ostream& stream,Pirate ob)
{
  stream << "id: " << ((_Pirate*)ob.ptr)->id  <<'\n';
  stream << "x: " << ((_Pirate*)ob.ptr)->x  <<'\n';
  stream << "y: " << ((_Pirate*)ob.ptr)->y  <<'\n';
  stream << "owner: " << ((_Pirate*)ob.ptr)->owner  <<'\n';
  stream << "health: " << ((_Pirate*)ob.ptr)->health  <<'\n';
  stream << "strength: " << ((_Pirate*)ob.ptr)->strength  <<'\n';
  return stream;
}
