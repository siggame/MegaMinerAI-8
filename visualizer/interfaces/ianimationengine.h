#ifndef IANIMATIONENGINE_H
#define IANIMATIONENGINE_H

#include <QtPlugin>
#include <list>
#include "common.h"

namespace visualizer
{

  class IAnimationEngine
  {
    public:

  };

  struct Anim
  {
    virtual float controlDuration() const = 0;
    virtual float totalDuration() const = 0;
    float startTime; 
    float endTime;
  };

  struct IAnimator
  {
    virtual void addKeyFrame( const SmartPointer<Anim>& a ) = 0;
    virtual void addSubFrame( int keyFrame, const SmartPointer<Anim>& a ) = 0;
  };

  struct AnimData
  {
  };

} // visualizer

Q_DECLARE_INTERFACE( visualizer::IAnimationEngine, "siggame.vis2.animationengine/0.1" );
Q_DECLARE_INTERFACE( visualizer::IAnimator, "siggame.vis2.animator/0.1" );

#endif
