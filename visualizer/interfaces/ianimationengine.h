#ifndef IANIMATIONENGINE_H
#define IANIMATIONENGINE_H

#include <QtPlugin>
#include <list>
#include "common.h"

namespace visualizer
{
  struct Anim
  {
    virtual float controlDuration() const = 0;
    virtual float totalDuration() const = 0;
    float startTime; 
    float endTime;
  }; // Anim

  struct AnimData
  {
  }; // AnimData

  struct IAnimator
  {
    virtual void addKeyFrame( const SmartPointer<Anim>& a ) = 0;
    virtual void addSubFrame( const size_t& keyFrame, const SmartPointer<Anim>& a ) = 0;

  }; // IAnimator
  
  class IAnimationEngine
  {
    public:
      virtual SmartPointer<IAnimator> getAnimator() = 0;
  }; // IAnimationEngine
  
  class Animatable
  {
    public:
      SmartPointer<IAnimator> m_anims;
      virtual AnimData* getData() = 0; 

  };

} // visualizer

Q_DECLARE_INTERFACE( visualizer::IAnimationEngine, "siggame.vis2.animationengine/0.1" );
//Q_DECLARE_INTERFACE( visualizer::IAnimator, "siggame.vis2.animator/0.1" );

#endif
