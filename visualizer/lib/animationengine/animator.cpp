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

    int i = 0;
    while( i < keyFrame )
    {
      i++;
      j++;
    }

    j->second.push_back( a );

  }

  const size_t& Animator::numKeyFrames()
  {
    return m_animList.size();
  }

  SmartPointer<IAnimator::Iiterator> Animator::begin()
  {

  }

  SmartPointer<IAnimator::Iiterator> Animator::end()
  {
    // Just a dummy class because I'm an idiot
  }
  
  void Animator::iterator::operator ++ ( int )
  {
  }

  SmartPointer<Anim> Animator::iterator::operator -> ()
  {

  }

  bool Animator::iterator::done()
  {
    
  }

} // visualizer
