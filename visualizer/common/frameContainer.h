#if 0
#ifndef FRAMECONTAINER_H
#define FRAMECONTAINER_H

#include <list>
#include "common.h"
#include "animationengine.h"

/*
FrameContainer notes:
- adding and removing frames should properly use mutex locks to avoid issues with multithreading
- The remove mutex should be separate from the add mutex since removing actually could affect playback
*/

namespace visualizer
{
  
  class FrameContainer: public IFrameContainer
  {
  public:
    void addFrame( std::list<SmartPointer<Animatable> >& frame );
    void removeFrame( size_t frameNum );


  private:
     // We're going to want to put this in a dedicated class so we can allow a mutex
    // to automatically lock and unlock around it.
    // Going to use a list so adding frames doesn't require a mutex.
    // Vector could cause issues on resizes
    std::list<std::list<SmartPointer<Animatable> > >* m_frames;

    // std::list<SmartPointer<Animatable> > should be wrapped up 

    //std::vector<std::list<SmartPointer<Animatable> >

  };

} // visualizer


#endif
#endif
