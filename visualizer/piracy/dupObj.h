#ifndef	DUPOBJ_H
#define DUPOBJ_H

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

#endif
