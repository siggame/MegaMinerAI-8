// -*-c++-*-

#include "Virus.h"
#include "game.h"


Virus::Virus(_Virus* pointer)
{
    ptr = (void*) pointer;
}

int Virus::id()
{
  return ((_Virus*)ptr)->id;
}

int Virus::x()
{
  return ((_Virus*)ptr)->x;
}

int Virus::y()
{
  return ((_Virus*)ptr)->y;
}

int Virus::owner()
{
  return ((_Virus*)ptr)->owner;
}

int Virus::level()
{
  return ((_Virus*)ptr)->level;
}

int Virus::movesLeft()
{
  return ((_Virus*)ptr)->movesLeft;
}


int Virus::move(int x, int y)
{
  return virusMove( (_Virus*)ptr, x, y);
}

int Virus::talk(char* message)
{
  return virusTalk( (_Virus*)ptr, message);
}



std::ostream& operator<<(std::ostream& stream,Virus ob)
{
  stream << "id: " << ((_Virus*)ob.ptr)->id  <<'\n';
  stream << "x: " << ((_Virus*)ob.ptr)->x  <<'\n';
  stream << "y: " << ((_Virus*)ob.ptr)->y  <<'\n';
  stream << "owner: " << ((_Virus*)ob.ptr)->owner  <<'\n';
  stream << "level: " << ((_Virus*)ob.ptr)->level  <<'\n';
  stream << "movesLeft: " << ((_Virus*)ob.ptr)->movesLeft  <<'\n';
  return stream;
}
