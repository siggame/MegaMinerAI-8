#ifndef ANIMATIONENGINE_H
#define ANIMATIONENGINE_H

#include "animator.h"
#include "../../interfaces/ianimationengine.h"
#include "common.h"

/////////////////////////////////////////////////////////
/// @class _AnimationEngine
/// @description The core animation engine for the 
/// visualizer.  
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
/// @function _AnimationEngine::getAnimator()
/// @brief This function follow the abstract factory 
/// pattern.  It returns the latest and greatest
/// animator class.
/// @return SmartPointer<IAnimator> is a smart pointer
/// which holds an instance of an actual animator
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
/// @function _AnimationEngine::buildAnimation( Frame& frame )
/// @brief This function must be applied to any frame
/// before the animation engine can handle it.  It properly
/// segments the animations for use in the renderer
/// @param frame The Frame that we're going to loop through
/// the animations in and segment.
/////////////////////////////////////////////////////////

namespace visualizer
{
  // AnimationEngine will need to rely heavily on TimeManager
  // and trusting the renderer to give it the right frame.
  class _AnimationEngine: public Module, public IAnimationEngine
  {
    public:
      static void setup();
      static void destroy();
      SmartPointer<IAnimator> getAnimator();
      
      void buildAnimations( Frame& frame );
    private:
     
  }; // _AnimationEngine

  extern _AnimationEngine *AnimationEngine;

} // visualizer


#endif
