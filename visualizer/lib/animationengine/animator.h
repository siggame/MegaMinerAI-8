#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "ianimationengine.h"

namespace visualizer
{
  struct Animator: public IAnimator
  {
    Animator() {}
    ~Animator() {}
    void addKeyFrame( const SmartPointer<Anim>& a );
    void addSubFrame( const int& keyFrame, const SmartPointer<Anim>& a );

    std::list<SmartPointer<Anim> > m_animList;
  };

} // visualizer

#endif
