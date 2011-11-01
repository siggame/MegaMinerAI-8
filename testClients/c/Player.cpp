// -*-c++-*-

#include "Player.h"
#include "game.h"


Player::Player(_Player* pointer)
{
    ptr = (void*) pointer;
}

int Player::id()
{
  return ((_Player*)ptr)->id;
}

char* Player::playerName()
{
  return ((_Player*)ptr)->playerName;
}

int Player::byteDollars()
{
  return ((_Player*)ptr)->byteDollars;
}

int Player::cycles()
{
  return ((_Player*)ptr)->cycles;
}

int Player::time()
{
  return ((_Player*)ptr)->time;
}


int Player::talk(char* message)
{
  return playerTalk( (_Player*)ptr, message);
}



std::ostream& operator<<(std::ostream& stream,Player ob)
{
  stream << "id: " << ((_Player*)ob.ptr)->id  <<'\n';
  stream << "playerName: " << ((_Player*)ob.ptr)->playerName  <<'\n';
  stream << "byteDollars: " << ((_Player*)ob.ptr)->byteDollars  <<'\n';
  stream << "cycles: " << ((_Player*)ob.ptr)->cycles  <<'\n';
  stream << "time: " << ((_Player*)ob.ptr)->time  <<'\n';
  return stream;
}
