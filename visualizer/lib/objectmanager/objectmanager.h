#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "../gameobject/gameobject.h"
#include "../timeline/timeline.h"

#include "../common.h"
#include <iostream>

typedef int ObjIdType;

class _ObjectManager : public Module
{
  public:
    void setSize(const unsigned int & turns, const unsigned int & frames)
    {
      m_objects.setSize( turns, frames );
    }

    unsigned int frames()
    {
      return m_objects.getFrames();
    }

    unsigned int turns()
    {
      return m_objects.getTurns();
    }

    bool reg(const ObjIdType & id, LookupSet<GameObject*,ObjIdType> & objset);
    bool reg(const ObjIdType & id, GameObject * obj, const unsigned int & turn, const unsigned int & frame);
    bool del(const ObjIdType & id, const unsigned int & turn, const unsigned int & frame);

    LookupNode<GameObject *,ObjIdType> * get(const ObjIdType & id, const unsigned int & turn, const unsigned int & frame);
    std::map<ObjIdType,LookupNode<GameObject*,ObjIdType>* > * getBucket(const unsigned int & turn, const unsigned int & frame)
    {
      return m_objects.bucket( turn, frame );
    }

    bool exists(const ObjIdType &, const unsigned int &, const unsigned int &);

    static void setup();
    static void destroy();

  private:
    typedef std::map<ObjIdType,LookupNode<GameObject*,ObjIdType> > Bucket;
    LookupTable<GameObject*,ObjIdType> m_objects;
};

extern _ObjectManager *ObjectManager;
#endif
