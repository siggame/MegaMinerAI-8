#include "getters.h"

DLLEXPORT int mappableGetId(_Mappable* ptr)
{
  return ptr->id;
}
DLLEXPORT int mappableGetX(_Mappable* ptr)
{
  return ptr->x;
}
DLLEXPORT int mappableGetY(_Mappable* ptr)
{
  return ptr->y;
}
DLLEXPORT int baseGetId(_Base* ptr)
{
  return ptr->id;
}
DLLEXPORT int baseGetX(_Base* ptr)
{
  return ptr->x;
}
DLLEXPORT int baseGetY(_Base* ptr)
{
  return ptr->y;
}
DLLEXPORT int baseGetOwner(_Base* ptr)
{
  return ptr->owner;
}
DLLEXPORT int baseGetSpawnsLeft(_Base* ptr)
{
  return ptr->spawnsLeft;
}
DLLEXPORT int playerGetId(_Player* ptr)
{
  return ptr->id;
}
DLLEXPORT char* playerGetPlayerName(_Player* ptr)
{
  return ptr->playerName;
}
DLLEXPORT int playerGetByteDollars(_Player* ptr)
{
  return ptr->byteDollars;
}
DLLEXPORT int playerGetCycles(_Player* ptr)
{
  return ptr->cycles;
}
DLLEXPORT int playerGetTime(_Player* ptr)
{
  return ptr->time;
}
DLLEXPORT int tileGetId(_Tile* ptr)
{
  return ptr->id;
}
DLLEXPORT int tileGetX(_Tile* ptr)
{
  return ptr->x;
}
DLLEXPORT int tileGetY(_Tile* ptr)
{
  return ptr->y;
}
DLLEXPORT int tileGetOwner(_Tile* ptr)
{
  return ptr->owner;
}
DLLEXPORT int virusGetId(_Virus* ptr)
{
  return ptr->id;
}
DLLEXPORT int virusGetX(_Virus* ptr)
{
  return ptr->x;
}
DLLEXPORT int virusGetY(_Virus* ptr)
{
  return ptr->y;
}
DLLEXPORT int virusGetOwner(_Virus* ptr)
{
  return ptr->owner;
}
DLLEXPORT int virusGetLevel(_Virus* ptr)
{
  return ptr->level;
}
DLLEXPORT int virusGetMovesLeft(_Virus* ptr)
{
  return ptr->movesLeft;
}
DLLEXPORT int virusGetLiving(_Virus* ptr)
{
  return ptr->living;
}

