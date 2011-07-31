#include "animator.h"

namespace visualizer
{

  void Animator::addKeyFrame( const SmartPointer<Anim>& a )
  {
    m_animList.push_back
      ( 
      pair<SmartPointer<Anim>, std::list<SmartPointer<Anim> > >
          ( 
          a, 
          std::list<SmartPointer<Anim> >()
          )
      );
  }

  void Animator::addSubFrame( const size_t& keyFrame, const SmartPointer<Anim>& a )
  {
    if( keyFrame >= numKeyFrames() )
      THROW( Exception, "Adding Subframe to nonexistent keyframe" );
    std::list< pair<SmartPointer<Anim>, std::list<SmartPointer<Anim> > >  >::iterator j = m_animList.begin();
    for
      ( 
      int i = 0; 
      i < keyFrame;
      i++, j++ 
      )
    {
    }

    j->second.push_back( a );

  }

  const size_t& Animator::numKeyFrames()
  {
    return m_animList.size();
  }

} // visualizer
