///////////////////////////////////////////////////////////////////////////////
/// @file animator.h
/// @description Contains implementation class for IAnimator which
/// holds an individual timeline for an object.  
///////////////////////////////////////////////////////////////////////////////
#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "ianimationengine.h"
// @TODO Probably should make m_anims private.

namespace visualizer
{

  ///////////////////////////////////////////////////////////////////////////////
  /// @class Animator
  /// @description The animator holds a timeline.  Each keyFrame in the timeline
  /// can hold multiple or no subFrames.  An iterator has been provided to 
  /// loop through all the frames, in order.
  ///////////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////////////
  /// @fn Animator::addKeyFrame( const SmartPointer<Anim>& a )
  /// @brief Adds a keyframe to the timeline.  Any drawn object should probably
  /// have a Start and an End keyframe.
  /// @param a The animation type to put on the timeline.
  ///////////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////////////
  /// @fn Animator::addSubFrame
  ///     ( const size_t& keyFrame, const SmartPointer<Anim>& a )
  /// @brief Adds a subframe attached to an existing keyframe on the timeline.
  /// @pre The keyFrame must already exist.
  /// @param a The animation type to put on the timeline.
  ///////////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////////////
  /// @fn Animator::numKeyFrames()
  /// @brief Returns the number of key frames currently present on the timeline
  /// @return size_t& Represents the number of key frames present.
  ///////////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////////////
  /// @fn Animator::begin()
  /// @brief Returns an iterator pointing to the first animation on the timeline
  /// @return SmartPointer<Iiterator> Iterator
  ///////////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////////////
  /// @fn Animator::end()
  /// @brief Returns nothing.  Do Not Use.
  /// @pre DON'T USE.  SCHEDULED FOR REMOVAL
  /// @post KERPOW
  ///////////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////////////
  /// @class Animator::iterator
  /// @brief An iterator to loop through all the anim's on the Animator
  /// @note THIS IS NOT THREADSAFE
  ///////////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////////////
  /// @fn Animator::iterator::operator ++ ( int )
  /// @brief Post-order increment operator which goes to the next anim on the
  /// list.
  /// @pre Must not already be pointing to the last item on the list.
  ///////////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////////////
  /// @fn Animator::iterator::operator ->()
  /// @brief Arrow operator overload accessing the Anim under the iterator.
  /// @return SmartPointer<Anim> pointing to the desired Anim
  ///////////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////////////
  /// @fn Animator::iterator::done()
  /// @brief Returns true/false based on whether we've looped through everything
  /// or not.
  /// @return bool representing if we're done or not.
  ///////////////////////////////////////////////////////////////////////////////

  struct Animator: public IAnimator
  {
    void addKeyFrame( const SmartPointer<Anim>& a );
    void addSubFrame( const size_t& keyFrame, const SmartPointer<Anim>& a );

    const size_t& numKeyFrames();

    class iterator: public Iiterator
    {
      public:
        iterator
          ( 
            std::list< pair<SmartPointer<Anim>, std::list<SmartPointer<Anim> > > >::iterator i,
            std::list< pair<SmartPointer<Anim>, std::list<SmartPointer<Anim> > > >::iterator end 
          );
        void operator ++ ( int );
        SmartPointer<Anim> operator -> ();
        bool done();
      private:
        std::list< pair<SmartPointer<Anim>, std::list<SmartPointer<Anim> > > >::iterator m_iter;
        std::list< pair<SmartPointer<Anim>, std::list<SmartPointer<Anim> > > >::iterator m_end;
        std::list< SmartPointer<Anim> >::iterator m_subIter;
        bool m_keyFrame;
        bool m_done;
    };

    SmartPointer<Iiterator> begin();
    SmartPointer<Iiterator> end();

    std::list< pair<SmartPointer<Anim>, std::list<SmartPointer<Anim> > >  > m_animList;
  }; // Animator 

} // visualizer

#endif
