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
	//get()->m_objects.
    }

    unsigned int frames()
    {
    }

    unsigned int turns();

    static bool reg(const ObjIdType & id, GameObject * obj, const unsigned int & turn, const unsigned int & frame);
    static bool del(const ObjIdType & id, const unsigned int & turn, const unsigned int & frame);
    static GameObject * get(const ObjIdType & id, const unsigned int & turn, const unsigned int & frame);

private:
    LookupTable<ObjIdType,GameObject*> m_objects;
};

#endif
