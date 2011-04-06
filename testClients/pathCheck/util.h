#ifndef UTIL_H
#define UTIL_H

#include "structures.h"


#ifdef __cplusplus
extern "C"
{
#endif
  //pathfinding

  int getPathSize();
  int getPathStep(int i);
  int findPath(_Tile* start, _Tile* end, int type);
  
#ifdef __cplusplus
}
#endif

#endif
