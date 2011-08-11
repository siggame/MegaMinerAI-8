#include "animationengine.h"

namespace visualizer
{
  _AnimationEngine *AnimationEngine = 0;

  void _AnimationEngine::setup()
  {
    if( !AnimationEngine )
    {
      AnimationEngine = new _AnimationEngine;
    }
    else
    {
      THROW( Exception, "Animation Engine already initialized." );
    }
  }

  void _AnimationEngine::destroy()
  {
    delete AnimationEngine;
    AnimationEngine = 0;
  }

  SmartPointer<IAnimator> _AnimationEngine::getAnimator()
  {
    return new Animator();
  }

  void _AnimationEngine::buildAnimations( Frame& frame )
  {
    for
      ( 
      std::list<SmartPointer<Animatable> >::iterator i = frame.getAnimations().begin();
      i != frame.getAnimations().end();
      i++ 
      )
    {
      IAnimator& anim = (*i)->getAnimationSequence( 0 );
      for
        (
        SmartPointer<IAnimator::Iiterator> j = anim.begin();
        j->done();
        (*j)++
        )
      {
      }

    }
  }

} // visualizer


