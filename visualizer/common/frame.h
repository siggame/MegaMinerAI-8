#ifndef FRAME_H
#define FRAME_H

#include "common.h"
#include "animatable.h"
#include <list>

namespace visualizer
{
  class Frame
  {
    public:
      void addAnimatable( const SmartPointer<Animatable>& animatable );
      std::list<SmartPointer<Animatable> >& getAnimations();
      const size_t size() const;

    private:
      std::list<SmartPointer<Animatable> > m_frame;

  }; // Frame

} // visualizer

#endif
