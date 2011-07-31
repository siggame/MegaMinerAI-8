#ifndef IANIMATIONENGINE_H
#define IANIMATIONENGINE_H

#include <list>
#include "common.h"

namespace visualizer
{

  class IAnimationEngine
  {
    public:

  };

  struct AnimData
  {
  };

  struct Anim
  {
    virtual float controlDuration() const = 0;
    virtual float totalDuration() const = 0;
    float startTime;
    float endTime;
  };

  struct Animator
  {
    std::list<SmartPointer<Anim> > m_animList;
    //std::list<int > m_animList;
  };

} // visualizer

#endif
