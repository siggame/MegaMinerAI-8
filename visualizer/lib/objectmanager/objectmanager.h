#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "../singleton.h"
#include "../gameobject/gameobject.h"
#include "../timeline/lookupTable/lookuptable.h"

typedef int ObjIdType;

class ObjectManager : public Singleton<ObjectManager>
{
public:
    static void setSize(const unsigned int & turns, const unsigned int & frames)
    {
	if (!Singleton<ObjectManager>::isInit())
	    return;
	Singleton<ObjectManager>::get()->m_objects.setSize(turns,frames);
    }

    static unsigned int frames()
    {
	if (!Singleton<ObjectManager>::isInit())
	    return 0;
	return Singleton<ObjectManager>::get()->m_objects.getFrames();
    }

    static unsigned int turns()
    {
	if (!Singleton<ObjectManager>::isInit())
	    return 0;
	return Singleton<ObjectManager>::get()->m_objects.getTurns();
    }


    static bool reg(const ObjIdType & id, LookupSet<GameObject*,ObjIdType> objset);
    static bool reg(const ObjIdType & id, GameObject * obj, const unsigned int & turn, const unsigned int & frame);
    static bool del(const ObjIdType & id, const unsigned int & turn, const unsigned int & frame);
    static LookupNode<GameObject *,ObjIdType> * get(const ObjIdType & id, const unsigned int & turn, const unsigned int & frame);

    static bool exists(const ObjIdType & id, const unsigned int & turn, const unsigned int & frame){return true;} //! @todo FIX THIS
    static bool destroy();
    ObjectLoader::destroy();

private:
    typedef Singleton<ObjectManager> Single;
    LookupTable<GameObject*,ObjIdType> m_objects;
};

#endif
