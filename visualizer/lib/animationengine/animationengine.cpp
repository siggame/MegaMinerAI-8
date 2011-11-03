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

  void _AnimationEngine::buildAnimations( Frame& frame )
  {
    for
      ( 
      std::list<SmartPointer<Animatable> >::iterator i = frame.getAnimations().begin();
      i != frame.getAnimations().end();
      i++ 
      )
    {
      // Total duration is the total amount of time units 
      // in the animation.
      float totalDuration = 0;
      // extraTime is used to assist in calculating the total duration
      // if there are extra animations left over
      float extraTime = 0;
      // Temporary variable for expanding extratime
      float exT;
      for
        (
        std::list<SmartPointer<Anim> >::iterator j = (*i)->getFrames().begin();
        j != (*i)->getFrames().end();
        j++
        )
      {
        // totalDuration is at the very minimum the summation of the "control" durations.
        totalDuration += (*j)->controlDuration();
        // Calculate the extra time for just this animation
        exT = (*j)->totalDuration() - (*j)->controlDuration();
        // Build up the total extraTime
        // If the left over extraTime is greater than the new exT, adjust it appropriately
        extraTime = (extraTime - (*j)->controlDuration()) > exT ? (extraTime - (*j)->controlDuration()) : exT;
      }

      // Set the full relative duration to the total control durations and any remaining time.
      float fullTime = totalDuration + extraTime;
      float start = 0;
      for
        (
        std::list<SmartPointer<Anim> >::iterator j = (*i)->getFrames().begin();
        j != (*i)->getFrames().end();
        j++
        )
      {
        // Set the animation start time
        (*j)->startTime = start;
        // Calculate the relative animation end time based off of the start time.
        (*j)->endTime = (*j)->startTime + ((*j)->totalDuration()/fullTime);
        // Calculate the next start time based off of the control duration.
        start = (*j)->startTime + ((*j)->controlDuration()/fullTime);
      }

    }

  } // _AnimationEngine::buildAnimations()

  void _AnimationEngine::draw()
  {
    m_animMutex.lock();
    if( m_frameList )
    {
      Frame& frame = (*m_frameList)[ TimeManager->getTurn() ];

      for
        (
        std::list<SmartPointer<Animatable> >::iterator i = frame.getAnimations().begin();
        i != frame.getAnimations().end();
        i++
        )
      {
        drawAnim( *(*i) );
      }
    }
    m_animMutex.unlock();

  } // _AnimationEngine::draw()

  void _AnimationEngine::drawAnim( Animatable& animator )
  {
    int c = 0;
    for
      (
      std::list<SmartPointer<Anim> >::iterator i = animator.getFrames().begin();
      i != animator.getFrames().end();
      i++
      )
    {
      animator.getData();
      (*i)->animate( TimeManager->getTurnPercent(), animator.getData() );
    }

  } // _AnimationEngine::drawAnim()

  void _AnimationEngine::registerFrameContainer( AnimSequence* frameList )
  {
    m_animMutex.lock();
      m_frameList = frameList;
    m_animMutex.unlock();
  } // _AnimationEngine::registerFrameContainer()

} // visualizer


