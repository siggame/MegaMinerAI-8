#ifndef IOBJECTMANAGER_H
#define IOBJECTMANAGER_H

#include "../lib/timeline/timeline.h"
#include "../lib/gameobject/gameobject.h"
#include <QtPlugin>

namespace visualizer
{

  typedef int ObjIdType;

  class IObjectManager
  {
    public:
      virtual void setSize( const unsigned int& turns, const unsigned int& frames ) = 0;
      virtual unsigned int frames() = 0;
      virtual unsigned int turns() = 0;

      virtual bool reg
        ( 
        const ObjIdType& id, 
        LookupSet<GameObject*, ObjIdType>& objset 
        ) = 0;

      virtual bool reg
        ( 
        const ObjIdType& id, 
        GameObject* obj, 
        const unsigned int& turn, 
        const unsigned int& frame
        ) = 0;

      virtual bool del
        (
        const ObjIdType& id,
        const unsigned int& turn,
        const unsigned int& frame
        ) = 0;

      virtual bool exists
        (
        const ObjIdType&,
        const unsigned int&, 
        const unsigned int&
        ) = 0;
  };

} // visualizer

Q_DECLARE_INTERFACE( visualizer::IObjectManager, "siggame.vis2.objectmanager/0.1" );

#endif 
