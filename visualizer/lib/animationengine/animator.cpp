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
    return SmartPointer<IAnimator::Iiterator>(new iterator( m_animList.begin(), m_animList.end() ));
  }

  SmartPointer<IAnimator::Iiterator> Animator::end()
  {
    // Just a dummy procedure because I'm an idiot
  }
  
  Animator::iterator::iterator
    ( 
      std::list< pair<SmartPointer<Anim>, std::list<SmartPointer<Anim> > > >::iterator i, 
      std::list< pair<SmartPointer<Anim>, std::list<SmartPointer<Anim> > > >::iterator end 
    )
  {
    m_iter = i;
    m_end = end;
    m_subIter = i->second.begin();
    m_keyFrame = true;
    m_done = false;
  }

  void Animator::iterator::operator ++ ( int )
  {
    if( m_keyFrame )
    {
      m_keyFrame = false;
      m_subIter = m_iter->second.begin();
    }
    else
    {
      m_subIter++;
    }
    
    if( m_subIter == m_iter->second.end() )
    {
      m_keyFrame = true;
      m_iter++;
    }

    if( m_iter == m_end )
    {
      m_done = true;
    }

  }

  SmartPointer<Anim> Animator::iterator::operator -> ()
  {
    if( m_keyFrame )
    {
      return m_iter->first;
    }
    else
    {
      return *m_subIter;
    }

  }

  bool Animator::iterator::done()
  {
    return m_done;
  }

} // visualizer
