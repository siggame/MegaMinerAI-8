#include "animatable.h"
#include "ianimationengine.h"

namespace visualizer
{

  IAnimator& Animatable::getAnimationSequence( IAnimationEngine* animEngine )
  {
    if( !m_animationSequence )
    {
      if( !animEngine )
      {
        THROW
          ( 
          Exception,
          "Animation Engine Is Null Pointer.  This Should Only Occur When buildAnimations is called."
          );
      }
      m_animationSequence = animEngine->getAnimator();
    }
    return *m_animationSequence;
  } // Animatable::getAnimationSequence()

} // visualizer
