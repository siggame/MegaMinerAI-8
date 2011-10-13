#ifndef IRENDER_H
#define IRENDER_H

#include <QtPlugin>
#include "animsequence.h"
#include "iobjectmanager.h"
#include "models.h"

namespace visualizer
{

  //this is a place holder
  typedef GameObject renderObj;

  class IRenderer
  {
    public:
      enum Alignment
      {
        Left, 
        Right, 
        Center
      };

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

      virtual void setColor
        ( 
        const Color& c
        ) const = 0;

      virtual void drawQuad
        (
        const float& x,
        const float& y,
        const float& w,
        const float& h,
        const float& z = 0.0f
        ) const = 0;

      virtual void drawTexturedQuad
        (
        const float& x,
        const float& y,
        const float& w, 
        const float& h, 
        const std::string& resource,
        const float& z = 0.0f
        ) const = 0;

      virtual void drawAnimQuad
        (
        const float& x, 
        const float& y,
        const float& w, 
        const float& h,
        const std::string& resource,
        const int& frameNumber = 0,
        const float& z = 0.0f
        ) const = 0;

      virtual void drawProgressBar
        (
        const float& x,
        const float& y,
        const float& w,
        const float& h,
        const float& percent,
        const Color& color = Color( 0, 0, 0, 1 ),
        const float& lineWidth = 1,
        const float& z = 0.0f
        ) const = 0;

      virtual void drawText
        (
        const float& x,
        const float& y,
        const std::string& line, 
        const float& size = 15.0f, 
        const Alignment& a = Left
        ) const = 0;
  };

} // visualizer

Q_DECLARE_INTERFACE( visualizer::IRenderer, "siggame.vis2.renderer/0.1" );

#endif
