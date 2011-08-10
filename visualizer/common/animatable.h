#ifndef ANIMATABLE_H
#define ANIMATABLE_H

#include "ianimationengine.h"

/////////////////////////////////////////////////
/// @class Animatable 
/// @brief Base Class for any object you want to associate animations with.
/////////////////////////////////////////////////

/////////////////////////////////////////////////
/// @fn Animatable::getAnimationSequence( IAnimationEngine* animEngine )
/// @brief Gets the IAnimator defined by the core engine and saves it.
/// @param animEngine The interface to the core engine passed through on 
///  initialization.
/////////////////////////////////////////////////

/////////////////////////////////////////////////
/// @fn Animatable::getData()
/// @brief Virtual function which gets the 
/// animation specific storage structure the 
/// animator uses. 
////////////////////////////////////////////////

namespace visualizer
{
  class Animatable
  {
    public:
      IAnimator& getAnimationSequence( IAnimationEngine* animEngine )
      {
        if( !m_animationSequence )
        {
          m_animationSequence = animEngine->getAnimator();
        }
        return *m_animationSequence;
      }

      virtual AnimData* getData() = 0; 

    private:
      SmartPointer<IAnimator> m_animationSequence;

  }; // Animatable

} // visualizer

#endif // ANIMATABLE_H
