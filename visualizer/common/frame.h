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
      Frame()
      {
      }

      Frame( const Frame& frame )
      {
        /// @TODO Remove me
//        cout << "Copy Frame" << endl;
        m_frame = frame.m_frame;

      }

      virtual ~Frame() {}

      void addAnimatable( const SmartPointer<Animatable>& animatable );
      void addAnimatableFront( const SmartPointer<Animatable>& animatable );

      /// @TODO Should probably return a wrapped object
      std::list<SmartPointer<Animatable> >& getAnimations();
      const size_t size() const;

    private:
      std::list<SmartPointer<Animatable> > m_frame;

  }; // Frame

} // visualizer

#endif
