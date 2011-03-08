#include "getters.h"

int mappableGetId(_Mappable* ptr)
{
  return ptr->id;
}
int mappableGetX(_Mappable* ptr)
{
  return ptr->x;
}
int mappableGetY(_Mappable* ptr)
{
  return ptr->y;
}
int unitGetId(_Unit* ptr)
{
  return ptr->id;
}
int unitGetX(_Unit* ptr)
{
  return ptr->x;
}
int unitGetY(_Unit* ptr)
{
  return ptr->y;
}
int unitGetOwner(_Unit* ptr)
{
  return ptr->owner;
}
int unitGetHealth(_Unit* ptr)
{
  return ptr->health;
}
int unitGetStrength(_Unit* ptr)
{
  return ptr->strength;
}
int pirateGetId(_Pirate* ptr)
{
  return ptr->id;
}
int pirateGetX(_Pirate* ptr)
{
  return ptr->x;
}
int pirateGetY(_Pirate* ptr)
{
  return ptr->y;
}
int pirateGetOwner(_Pirate* ptr)
{
  return ptr->owner;
}
int pirateGetHealth(_Pirate* ptr)
{
  return ptr->health;
}
int pirateGetStrength(_Pirate* ptr)
{
  return ptr->strength;
}
int portGetId(_Port* ptr)
{
  return ptr->id;
}
int portGetX(_Port* ptr)
{
  return ptr->x;
}
int portGetY(_Port* ptr)
{
  return ptr->y;
}
int portGetOwner(_Port* ptr)
{
  return ptr->owner;
}
int shipGetId(_Ship* ptr)
{
  return ptr->id;
}
int shipGetX(_Ship* ptr)
{
  return ptr->x;
}
int shipGetY(_Ship* ptr)
{
  return ptr->y;
}
int shipGetOwner(_Ship* ptr)
{
  return ptr->owner;
}
int shipGetHealth(_Ship* ptr)
{
  return ptr->health;
}
int shipGetStrength(_Ship* ptr)
{
  return ptr->strength;
}
int tileGetId(_Tile* ptr)
{
  return ptr->id;
}
int tileGetX(_Tile* ptr)
{
  return ptr->x;
}
int tileGetY(_Tile* ptr)
{
  return ptr->y;
}
int tileGetType(_Tile* ptr)
{
  return ptr->type;
}
int treasureGetId(_Treasure* ptr)
{
  return ptr->id;
}
int treasureGetX(_Treasure* ptr)
{
  return ptr->x;
}
int treasureGetY(_Treasure* ptr)
{
  return ptr->y;
}
_Pirate* treasureGetPirate(_Treasure* ptr)
{
  return ptr->pirate;
}

