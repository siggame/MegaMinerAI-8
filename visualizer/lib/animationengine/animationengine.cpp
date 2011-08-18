#include "animationengine.h"

namespace visualizer
{
  _AnimationEngine *AnimationEngine = 0;

  _AnimationEngine::_AnimationEngine()
  {
    m_frameList = 0;

  } // _AnimationEngine::_AnimationEngine()

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
    return SmartPointer<IAnimator>( new Animator() );

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
#if 0
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
#endif
    }

  } // _AnimationEngine::buildAnimations()

  void _AnimationEngine::draw()
  {
    if( m_frameList )
    {
#if 0
      cout << "Turn: " << TimeManager->getTurn() << endl;
      Frame& frame = (*m_frameList)[TimeManager->getTurn()];
      std::list<SmartPointer<Animatable> >& anims = frame.getAnimations();

      for
        (
        std::list<SmartPointer<Animatable> >::iterator i = anims.begin();
        i != anims.end();
        i++
        )
      {
        IAnimator& s = (*i)->getAnimationSequence( 0 );
        drawAnim( s );
      }
#endif
    }

  } // _AnimationEngine::draw()

  void _AnimationEngine::drawAnim( IAnimator& animator )
  {
    for
      (
      SmartPointer<IAnimator::Iiterator> i = animator.begin();
      !i->done();
      (*i)++
      )
    {

    }

  } // _AnimationEngine::drawAnim()

  void _AnimationEngine::registerFrameContainer( AnimSequence* frameList )
  {
    m_frameList = frameList;
  } // _AnimationEngine::registerFrameContainer()

} // visualizer


