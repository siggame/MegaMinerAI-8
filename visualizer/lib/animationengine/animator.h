#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "ianimationengine.h"

namespace visualizer
{
  struct Animator: public IAnimator
  {
    void addKeyFrame( const SmartPointer<Anim>& a );
    void addSubFrame( const size_t& keyFrame, const SmartPointer<Anim>& a );

    const size_t& numKeyFrames();

    std::list< pair<SmartPointer<Anim>, std::list<SmartPointer<Anim> > >  > m_animList;
  }; // Animator 

} // visualizer

#endif
