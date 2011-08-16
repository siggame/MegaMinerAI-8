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
  } // _AnimationEngine::setup()

  void _AnimationEngine::destroy()
  {
    delete AnimationEngine;
    AnimationEngine = 0;
  } // _AnimationEngine::destroy()

  SmartPointer<IAnimator> _AnimationEngine::getAnimator()
  {
    return new Animator();
  } // _AnimationEngine::getAnimator()

  void _AnimationEngine::buildAnimations( Frame& frame )
  {
    // @NOTE Can we simplify this looping any?  Not a huge issue since it's internal
    // if this were on the piracy side, I'd be a little more worried
    for
      ( 
      std::list<SmartPointer<Animatable> >::iterator i = frame.getAnimations().begin();
      i != frame.getAnimations().end();
      i++ 
      )
    {
      IAnimator& anim = (*i)->getAnimationSequence( 0 );
      float totalDuration = 0;
      float extraTime = 0;
      float exT;
      for
        (
        SmartPointer<IAnimator::Iiterator> j = anim.begin();
        (*j).done();
        (*j)++
        )
      {
        totalDuration += (*j)->controlDuration();
        exT = (*j)->totalDuration() - (*j)->controlDuration();
        extraTime = extraTime > exT ? extraTime : exT;
      }

      float fullTime = totalDuration + extraTime;
      float start = 0;
      for
        (
        SmartPointer<IAnimator::Iiterator> j = anim.begin();
        (*j).done();
        (*j)++
        )
      {
        (*j)->startTime = start;
        start = (*j)->endTime = (*j)->startTime + ((*j)->controlDuration()/fullTime);
      }
    }
  } // _AnimationEngine::buildAnimations()

  void _AnimationEngine::draw()
  {

  } // _AnimationEngine::draw()

  void _AnimationEngine::registerFrameContainer( AnimSequence* frameList )
  {
  } // _AnimationEngine::registerFrameContainer()

} // visualizer


