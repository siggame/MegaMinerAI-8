#include "animatable.h"
#include "ianimationengine.h"

namespace visualizer
{

#if 0
  IAnimator& Animatable::getAnimationSequence( IAnimationEngine* animEngine )
  {
    if( !m_animationSequence )
    {
      if( !animEngine )
      {
        THROW
          ( 
          Exception,
          "Animation Engine Is Null Pointer.  This Should Only Occur When Animations Already Exist."
          );
      }
      m_animationSequence = animEngine->getAnimator();
    }

    return *m_animationSequence;

  } // Animatable::getAnimationSequence()
#endif

  void Animatable::addKeyFrame( const Anim& anim )
  {
  } // Animatable::addKeyFrame()

  void Animatable::addSubFrame( const int& subFrame, const Anim& anim )
  {
  } // Animatable::addSubFrame()

  const int& Animatable::numKeyFrames() const
  {
  } // Animatable::numKeyFrames()

} // visualizer
