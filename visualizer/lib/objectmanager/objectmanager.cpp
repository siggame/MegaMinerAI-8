#include "objectmanager.h"

namespace visualizer
{

  _ObjectManager *ObjectManager;

  bool _ObjectManager::reg(const ObjIdType & id, GameObject * obj, const unsigned int & turn, const unsigned int & frame)
  {
    GameObject * temp = obj;

    //! @todo FILL IN
    return false;
  }


  bool _ObjectManager::del(const ObjIdType & id, const unsigned int & turn, const unsigned int & frame)
  {
    // if ()

    //! @todo FILL IN
    return true;
  }


  LookupNode<GameObject *,ObjIdType> * _ObjectManager::get(const ObjIdType & id, const unsigned int & turn, const unsigned int & frame )
  {
    #if 0
    if (!Singleton<_ObjectManager>::isInit())
      return NULL;
    #endif

    if (turn >= turns() || frame >= frames())
      return NULL;

    return m_objects.node(id,turn,frame);
  }


  bool _ObjectManager::exists(const ObjIdType & id, const unsigned int & turn, const unsigned int & frame)
  {
    return (m_objects.node(id, turn, frame) != NULL);
  }


  bool _ObjectManager::reg(const ObjIdType & id, LookupSet<GameObject*,ObjIdType> & objset)
  {
    m_objects.add(objset);
    return true;
  }


  void _ObjectManager::setup()
  {
    if( !ObjectManager )
    {
      ObjectManager = new _ObjectManager;
    }
    else
    {
      THROW( Exception, "Object Manager already initialized" );
    }
  }


  void _ObjectManager::destroy()
  {
    delete ObjectManager;
    ObjectManager = 0;
    //return _ObjectManager::destroy();
  }

} // visualizer
