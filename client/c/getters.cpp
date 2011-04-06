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
DLLEXPORT int unitGetId(_Unit* ptr)
{
  return ptr->id;
}
DLLEXPORT int unitGetX(_Unit* ptr)
{
  return ptr->x;
}
DLLEXPORT int unitGetY(_Unit* ptr)
{
  return ptr->y;
}
DLLEXPORT int unitGetOwner(_Unit* ptr)
{
  return ptr->owner;
}
DLLEXPORT int unitGetHealth(_Unit* ptr)
{
  return ptr->health;
}
DLLEXPORT int unitGetStrength(_Unit* ptr)
{
  return ptr->strength;
}
DLLEXPORT int unitGetHasMoved(_Unit* ptr)
{
  return ptr->hasMoved;
}
DLLEXPORT int unitGetHasAttacked(_Unit* ptr)
{
  return ptr->hasAttacked;
}
DLLEXPORT int pirateGetId(_Pirate* ptr)
{
  return ptr->id;
}
DLLEXPORT int pirateGetX(_Pirate* ptr)
{
  return ptr->x;
}
DLLEXPORT int pirateGetY(_Pirate* ptr)
{
  return ptr->y;
}
DLLEXPORT int pirateGetOwner(_Pirate* ptr)
{
  return ptr->owner;
}
DLLEXPORT int pirateGetHealth(_Pirate* ptr)
{
  return ptr->health;
}
DLLEXPORT int pirateGetStrength(_Pirate* ptr)
{
  return ptr->strength;
}
DLLEXPORT int pirateGetHasMoved(_Pirate* ptr)
{
  return ptr->hasMoved;
}
DLLEXPORT int pirateGetHasAttacked(_Pirate* ptr)
{
  return ptr->hasAttacked;
}
DLLEXPORT int playerGetId(_Player* ptr)
{
  return ptr->id;
}
DLLEXPORT char* playerGetPlayerName(_Player* ptr)
{
  return ptr->playerName;
}
DLLEXPORT int playerGetGold(_Player* ptr)
{
  return ptr->gold;
}
DLLEXPORT int playerGetTime(_Player* ptr)
{
  return ptr->time;
}
DLLEXPORT int portGetId(_Port* ptr)
{
  return ptr->id;
}
DLLEXPORT int portGetX(_Port* ptr)
{
  return ptr->x;
}
DLLEXPORT int portGetY(_Port* ptr)
{
  return ptr->y;
}
DLLEXPORT int portGetOwner(_Port* ptr)
{
  return ptr->owner;
}
DLLEXPORT int shipGetId(_Ship* ptr)
{
  return ptr->id;
}
DLLEXPORT int shipGetX(_Ship* ptr)
{
  return ptr->x;
}
DLLEXPORT int shipGetY(_Ship* ptr)
{
  return ptr->y;
}
DLLEXPORT int shipGetOwner(_Ship* ptr)
{
  return ptr->owner;
}
DLLEXPORT int shipGetHealth(_Ship* ptr)
{
  return ptr->health;
}
DLLEXPORT int shipGetStrength(_Ship* ptr)
{
  return ptr->strength;
}
DLLEXPORT int shipGetHasMoved(_Ship* ptr)
{
  return ptr->hasMoved;
}
DLLEXPORT int shipGetHasAttacked(_Ship* ptr)
{
  return ptr->hasAttacked;
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
DLLEXPORT int tileGetType(_Tile* ptr)
{
  return ptr->type;
}
DLLEXPORT int treasureGetId(_Treasure* ptr)
{
  return ptr->id;
}
DLLEXPORT int treasureGetX(_Treasure* ptr)
{
  return ptr->x;
}
DLLEXPORT int treasureGetY(_Treasure* ptr)
{
  return ptr->y;
}
DLLEXPORT int treasureGetPirateID(_Treasure* ptr)
{
  return ptr->pirateID;
}
DLLEXPORT int treasureGetAmount(_Treasure* ptr)
{
  return ptr->amount;
}

