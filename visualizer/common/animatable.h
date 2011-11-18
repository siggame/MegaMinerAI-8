#ifndef ANIMATABLE_H
#define ANIMATABLE_H

#include "ianimator.h"
#include <vector>
#include <list>

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
  class IRenderer;

  class Animatable
  {
    public:
      Animatable( IRenderer *renderer = 0 );
      virtual ~Animatable() {};
      virtual AnimData* getData() = 0; 

      void addKeyFrame( SmartPointer< Anim > anim );
      void addSubFrame( const size_t& subFrame, SmartPointer< Anim > anim );

      const size_t& numKeyFrames() const;
      const size_t& numFrames() const;

      std::list<SmartPointer<Anim> >& getFrames();
      const std::list<SmartPointer<Anim> >& getFrames() const;

      const IRenderer& renderer() const;
    private:
      std::vector< std::list<SmartPointer<Anim> >::iterator > m_keyFrames;
      std::list<SmartPointer<Anim> > m_frames;

      IRenderer *m_renderer;

  }; // Animatable

} // visualizer

#endif // ANIMATABLE_H
