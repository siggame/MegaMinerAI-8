#ifndef ANIMATABLE_H
#define ANIMATABLE_H

#include "ianimator.h"

namespace visualizer
{

  //////////////////////////////////////////////////////////////////////////////
  /// @class Animatable 
  /// @brief Base Class for any object you want to associate animations with.
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  /// @fn Animatable::getAnimationSequence( IAnimationEngine* animEngine )
  /// @brief Gets the IAnimator defined by the core engine and saves it.
  /// @param animEngine The interface to the core engine passed through on 
  ///  initialization.
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  /// @fn Animatable::getData()
  /// @brief Virtual function which gets the animation specific storage 
  /// structure the animator uses. 
  /// @return pointer to AnimData* which is just a base class.
  //////////////////////////////////////////////////////////////////////////////

  class IAnimationEngine;
  class Animatable
  {
    public:
      //IAnimator& getAnimationSequence( IAnimationEngine* animEngine );
      virtual AnimData* getData() = 0; 

      void addKeyFrame( const Anim& anim );
      void addSubFrame( const int& subFrame, const Anim& anim );
      const int& numKeyFrames() const;

    private:
      //SmartPointer<IAnimator> m_animationSequence;

  }; // Animatable

} // visualizer

#endif // ANIMATABLE_H
