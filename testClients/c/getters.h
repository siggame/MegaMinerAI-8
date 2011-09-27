#ifndef GETTERS_H 
#define GETTERS_H
#include "structures.h"

#ifdef _WIN32
#define DLLEXPORT extern "C" __declspec(dllexport)
#else
#define DLLEXPORT
#endif

#ifdef __cplusplus
extern "C" {
#endif

DLLEXPORT int mappableGetId(_Mappable* ptr);
DLLEXPORT int mappableGetX(_Mappable* ptr);
DLLEXPORT int mappableGetY(_Mappable* ptr);


DLLEXPORT int baseGetId(_Base* ptr);
DLLEXPORT int baseGetX(_Base* ptr);
DLLEXPORT int baseGetY(_Base* ptr);
DLLEXPORT int baseGetOwner(_Base* ptr);


DLLEXPORT int playerGetId(_Player* ptr);
DLLEXPORT char* playerGetPlayerName(_Player* ptr);
DLLEXPORT int playerGetByteDollars(_Player* ptr);
DLLEXPORT int playerGetCycles(_Player* ptr);


DLLEXPORT int tileGetId(_Tile* ptr);
DLLEXPORT int tileGetX(_Tile* ptr);
DLLEXPORT int tileGetY(_Tile* ptr);
DLLEXPORT int tileGetOwner(_Tile* ptr);


DLLEXPORT int virusGetId(_Virus* ptr);
DLLEXPORT int virusGetX(_Virus* ptr);
DLLEXPORT int virusGetY(_Virus* ptr);
DLLEXPORT int virusGetOwner(_Virus* ptr);
DLLEXPORT int virusGetLevel(_Virus* ptr);



#ifdef __cplusplus
}
#endif

#endif
