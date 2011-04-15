#ifndef	DUPOBJ_H
#define DUPOBJ_H
#include "gold.h"
#include "objecttype.h"
#include "piracylocations.h"
#include "../lib/goc_owner.h"

struct DupObj
{
	unsigned int objType;
	unsigned int gold;
	unsigned int pirates;
	unsigned int owner;
	unsigned int time;
	unsigned int index;

	DupObj & operator+=(const DupObj & obj)
	{
		if (obj.time == time)
		{
		gold += obj.gold;
		pirates += obj.pirates;
		return *this;
		}

		gold = obj.gold;
		pirates = obj.pirates;
		owner = obj.owner;
		time = obj.time;

		//! @todo object type precedences: ex ship over pirate, pirate over treasure
		objType = objType;
		return *this;
	}

};

template<typename DupObject>
void setDupObj(GameObject * object, DupObject & dup)
{
    if (!object)
	return;//! @todo fuck off

    dup.gold = ((Gold*)(object->getGOC("Gold")))->gold();
    dup.owner = ((GOC_Owner*)(object->getGOC("Owner")))->owner();

    PiracyObjectType ot = ((ObjectType*)(object->getGOC("ObjectType")))->type();

    switch (ot)
    {
    case POT_PIRATE:
	dup.objType = POT_PIRATE;
	dup.pirates = 1;
	break;
    case POT_SHIP:
	dup.objType = POT_SHIP;
	dup.pirates = 0;
	break;
    case POT_PORT:
	dup.objType = POT_PORT;
	dup.pirates = 0;
	break;
    case POT_TREAS:
	dup.objType = POT_TREAS;
	dup.pirates = 0;
	break;
    default:
	//fuckoff
	dup = dup;
    }



}


#endif
