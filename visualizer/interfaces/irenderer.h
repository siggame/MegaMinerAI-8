#ifndef IRENDER_H
#define IRENDER_H

#include <QtPlugin>
#include "animsequence.h"
#include "iobjectmanager.h"

namespace visualizer
{

  //this is a place holder
  typedef GameObject renderObj;

  class IRenderer
  {
    public:
      virtual bool registerConstantObj( const unsigned int& id, renderObj* obj ) = 0;
      virtual bool deleteConstantObj( const unsigned int& id ) = 0;

      virtual bool refresh() = 0;
      virtual bool resize
        (
        const unsigned int& width,
        const unsigned int& height,
        const unsigned int& depth
        ) = 0;

      virtual bool isSetup() = 0;

      virtual unsigned int height() = 0;
      virtual unsigned int width() = 0;
      virtual unsigned int depth() = 0;

      virtual bool update
        (
        const unsigned int& turn,
        const unsigned int& frame
        ) = 0;

      virtual void update() = 0;

     
  };

} // visualizer

Q_DECLARE_INTERFACE( visualizer::IRenderer, "siggame.vis2.renderer/0.1" );

#endif
