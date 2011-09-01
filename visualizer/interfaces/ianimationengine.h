#ifndef IANIMATIONENGINE_H
#define IANIMATIONENGINE_H

#include <QtPlugin>
#include <list>
#include <vector>
#include "common.h"
#include "frame.h"
#include "ianimator.h"
#include "animsequence.h"

namespace visualizer
{
  class IAnimationEngine
  {
    public:
      //virtual SmartPointer<IAnimator> getAnimator() = 0;
      virtual void buildAnimations( Frame& frame ) = 0;

      // @TODO: Change this to a smart pointer or something similar so we know when the game is dead and 
      // we don't accidentally use it once Piracy has been destroyed.
      virtual void registerFrameContainer( AnimSequence* frameList ) = 0;
 
  }; // IAnimationEngine

  class IFrameContainer
  {
    public:
      
  }; // IFrameContainer

} // visualizer

Q_DECLARE_INTERFACE( visualizer::IAnimationEngine, "siggame.vis2.animationengine/0.1" );
//Q_DECLARE_INTERFACE( visualizer::IAnimator, "siggame.vis2.animator/0.1" );

#endif
