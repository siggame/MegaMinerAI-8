#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "../singleton.h"
#include "../gameobject/gameobject.h"
#include "../timeline/lookupTable/lookuptable.h"

typedef int ObjIdType;

class ObjectManager : public Singleton<ObjectManager>
{
public:
    void setSize(const unsigned int & turns, const unsigned int & frames)
    {
	if (!Singleton<ObjectManager>::isInit())
	    return;
	Singleton<ObjectManager>::get()->m_objects.setSize(turns,frames);
    }

    unsigned int frames()
    {
	if (!Singleton<ObjectManager>::isInit())
	    return 0;
	return Singleton<ObjectManager>::get()->m_objects.getFrames();
    }

    unsigned int turns()
    {
	if (!Singleton<ObjectManager>::isInit())
	    return 0;
	return Singleton<ObjectManager>::get()->m_objects.getTurns();
    }

    static bool reg(const ObjIdType & id, GameObject * obj, const unsigned int & turn, const unsigned int & frame);
    static bool del(const ObjIdType & id, const unsigned int & turn, const unsigned int & frame);
    static GameObject * get(const ObjIdType & id, const unsigned int & turn, const unsigned int & frame);

    static bool exists(const ObjIdType & id, const unsigned int & turn, const unsigned int & frame);

private:
    LookupTable<ObjIdType,GameObject*> m_objects;
};

#endif
