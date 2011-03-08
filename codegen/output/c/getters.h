#ifndef GETTERS_H 
#define GETTERS_H
#include "structures.h"

#ifdef __cplusplus
extern "C" {
#endif

int mappableGetId(_Mappable* ptr);
int mappableGetX(_Mappable* ptr);
int mappableGetY(_Mappable* ptr);


int unitGetId(_Unit* ptr);
int unitGetX(_Unit* ptr);
int unitGetY(_Unit* ptr);
int unitGetOwner(_Unit* ptr);
int unitGetHealth(_Unit* ptr);
int unitGetStrength(_Unit* ptr);


int pirateGetId(_Pirate* ptr);
int pirateGetX(_Pirate* ptr);
int pirateGetY(_Pirate* ptr);
int pirateGetOwner(_Pirate* ptr);
int pirateGetHealth(_Pirate* ptr);
int pirateGetStrength(_Pirate* ptr);


int portGetId(_Port* ptr);
int portGetX(_Port* ptr);
int portGetY(_Port* ptr);
int portGetOwner(_Port* ptr);


int shipGetId(_Ship* ptr);
int shipGetX(_Ship* ptr);
int shipGetY(_Ship* ptr);
int shipGetOwner(_Ship* ptr);
int shipGetHealth(_Ship* ptr);
int shipGetStrength(_Ship* ptr);


int tileGetId(_Tile* ptr);
int tileGetX(_Tile* ptr);
int tileGetY(_Tile* ptr);
int tileGetType(_Tile* ptr);


int treasureGetId(_Treasure* ptr);
int treasureGetX(_Treasure* ptr);
int treasureGetY(_Treasure* ptr);
_Pirate* treasureGetPirate(_Treasure* ptr);



#ifdef __cplusplus
}
#endif

#endif
