#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "../singleton.h"
#include "../gameobject/gameobject.h"
#include "../timeline/timeline.h"
#include <iostream>

typedef int ObjIdType;

class ObjectManager : public Singleton<ObjectManager>
{
public:
    static void setSize(const unsigned int & turns, const unsigned int & frames)
    {
      ObjectManager::instance()->m_objects.setSize( turns, frames );
    }

    static unsigned int frames()
    {
      return ObjectManager::instance()->m_objects.getFrames();
    }

    static unsigned int turns()
    {
      return ObjectManager::instance()->m_objects.getTurns();
    }


    static bool reg(const ObjIdType & id, LookupSet<GameObject*,ObjIdType> & objset);
    static bool reg(const ObjIdType & id, GameObject * obj, const unsigned int & turn, const unsigned int & frame);
    static bool del(const ObjIdType & id, const unsigned int & turn, const unsigned int & frame);

    static LookupNode<GameObject *,ObjIdType> * get(const ObjIdType & id, const unsigned int & turn, const unsigned int & frame);
    static std::map<ObjIdType,LookupNode<GameObject*,ObjIdType>* > * getBucket(const unsigned int & turn, const unsigned int & frame)
    {
      return ObjectManager::instance()->m_objects.bucket( turn, frame );
    }

    static bool exists(const ObjIdType &, const unsigned int &, const unsigned int &);
    static bool destroy();

private:
    typedef Singleton<ObjectManager> Single;
    typedef std::map<ObjIdType,LookupNode<GameObject*,ObjIdType> > Bucket;
    LookupTable<GameObject*,ObjIdType> m_objects;
};

#endif
