#ifndef	DUPOBJ_H
#define DUPOBJ_H
#include "gold.h"
#include "objecttype.h"
#include "piracylocations.h"
#include "../lib/goc_owner.h"
#include <GL/gl.h>
#include "../lib/resourcemanager/resourceman.h"

struct DupObj
{
	unsigned int objType;
	unsigned int gold;
	unsigned int pirates;
	unsigned int owner;
	unsigned int time;
	unsigned int index;
	unsigned int x, y;


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
		x = obj.x;
		y = obj.y;

		//! @todo object type precedences: ex ship over pirate, pirate over treasure
		objType = obj.objType;
		return *this;
	}

	void render()
	{
	    int i;


	    glTranslatef(x,y,0);
	    if (ResourceMan::isInit() && false)
	    {//! @todo: textures here
		switch (objType)
		{
		case POT_PIRATE:
		    break;
		case POT_SHIP:
		    break;
		case POT_PORT:
		    break;
		case POT_TREAS:
		    break;
		default:
		    //fuckoff
		    i=i;
		}

		glBegin(GL_QUADS);

		glVertex3f(0,0,-1); glTexCoord2f(0,0);
		glVertex3f(1,0,-1); glTexCoord2f(1,0);
		glVertex3f(1,1,-1); glTexCoord2f(1,1);
		glVertex3f(0,1,-1); glTexCoord2f(0,1);

		glEnd();
	    }
	    else
	    {
		//std::cout << "Render: l(" << x << "," << y << ") \n";
		glDisable(GL_BLEND);
		switch (objType)
		{
		case POT_PIRATE:
		    if (owner == 0)
			glColor4f(1,0,0,1);
		    else
			glColor4f(0,1,0,1);
		    break;
		case POT_SHIP:
		    if (owner == 0)
			glColor4f(1,.5,.5,1);
		    else
			glColor4f(.5,1,.5,1);

		    break;
		case POT_PORT:
		    if (owner == 0)
			glColor4f(.5,0,0,1);
		    else
			glColor4f(0,.5,0,1);
		    break;
		case POT_TREAS:
		    glColor4f(1,1,0,1);
		    break;
		default:
		    i=i;
		}

		glBegin(GL_QUADS);

		glVertex3d(0,0,1);
		glVertex3d(1,0,1);
		glVertex3d(1,1,1);
		glVertex3d(0,1,1);

		glEnd();

		glEnable(GL_BLEND);
	    }
	}

};

template<typename DupObject>
void setDupObj(GameObject * object, DupObject & dup)
{
    if (!object)
	return;//! @todo fuck off

    bool flag = false;

    GOComponent * goc = object->getGOC("ObjectType");
    PiracyObjectType ot;
    if (goc)
	ot = ((ObjectType*)(object->getGOC("ObjectType")))->type();
    else
    {
	ot = POT_NONE;
	std::cout << "object has no Type\n";
	flag = true;
    }

    goc = object->getGOC("Gold");
    if (goc)
	dup.gold = ((Gold*)(goc))->gold();
    else
    {
	dup.gold = 0;

	flag = ot != POT_PORT;
	if(flag)
	  std::cout << "object has no gold\n";
    }

    goc = object->getGOC("Owner");
    if (goc)
	dup.owner = ((GOC_Owner*)(goc))->owner();
    else
    {
	dup.owner = -1;

	flag = ot != POT_TREAS;
	if(flag)
	    std::cout << "object has no Owner\n";
    }



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
	std::cout << "AAAHHH!!! NO OBJECT TYPE!!\n";
    }


    if (flag)
    {
	std::cout << "Component List:\n";
	std::vector<GOC_IDType> components = object->listComponentFamilies();
	for (unsigned int i = 0; i < components.size(); i++)
	{
	    std::cout << "comp " << i << ": " << components[i] << '\n';
	}
    }
}


#endif
