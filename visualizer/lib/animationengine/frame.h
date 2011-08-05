#ifndef FRAME_H
#define FRAME_H

#include "common.h"
#include "animationengine.h"

namespace visualizer
{
  class Frame: public IFrame
  {
    public:
      void addAnimatable( const SmartPointer<Animatable>& animatable );
      std::list<SmartPointer<Animatable> >& getFrame();
      const size_t& size() const;

    private:
      std::list<SmartPointer<Animatable> > m_frame;

  }; // Frame

} // visualizer


#endif
