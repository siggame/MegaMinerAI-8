#ifndef ANIMSEQUENCE_H
#define ANIMSEQUENCE_H

#include "frame.h"

namespace visualizer
{

  class AnimSequence
  {
    public:
    //TODO: Update to Frame
      void addFrame( const Frame& frame )
      {
        m_frames.push_back( frame );
      }

      const size_t size() const
      {
        return m_frames.size();
      }

     private:
      std::list<Frame> m_frames;

  }; // AnimSequence

} // visualizer

#endif // ANIMSEQUENCE_H
