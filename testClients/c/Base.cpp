// -*-c++-*-

#include "Base.h"
#include "game.h"


Base::Base(_Base* pointer)
{
    ptr = (void*) pointer;
}

int Base::id()
{
  return ((_Base*)ptr)->id;
}

int Base::x()
{
  return ((_Base*)ptr)->x;
}

int Base::y()
{
  return ((_Base*)ptr)->y;
}

int Base::owner()
{
  return ((_Base*)ptr)->owner;
}

int Base::spawnsLeft()
{
  return ((_Base*)ptr)->spawnsLeft;
}


int Base::spawn(int Level)
{
  return baseSpawn( (_Base*)ptr, Level);
}



std::ostream& operator<<(std::ostream& stream,Base ob)
{
  stream << "id: " << ((_Base*)ob.ptr)->id  <<'\n';
  stream << "x: " << ((_Base*)ob.ptr)->x  <<'\n';
  stream << "y: " << ((_Base*)ob.ptr)->y  <<'\n';
  stream << "owner: " << ((_Base*)ob.ptr)->owner  <<'\n';
  stream << "spawnsLeft: " << ((_Base*)ob.ptr)->spawnsLeft  <<'\n';
  return stream;
}
