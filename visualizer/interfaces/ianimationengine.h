#ifndef IANIMATIONENGINE_H
#define IANIMATIONENGINE_H

#include <list>
#include "smartpointer.h"

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
    virtual const float& controlDuration() const = 0;
    virtual const float& totalDuration() const = 0;
    float startTime;
    float endTime;
  };

  struct Animator
  {
    std::list<SmartPointer<Anim> > m_animList;
  };

} // visualizer

#endif
