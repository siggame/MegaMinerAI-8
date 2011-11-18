#ifndef ANIMSEQUENCE_H
#define ANIMSEQUENCE_H

#include "frame.h"

namespace visualizer
{

  class AnimSequence
  {
    public:
      /// @TODO Update to Frame
      void addFrame( const Frame& frame )
      {
        m_frames.push_back( frame );
      }

      const size_t size() const
      {
        return m_frames.size();
      }

      Frame& operator [] (int frameNum)
      {
        /// @TODO Fix this.  It's not a vector because it
        /// resizes and causes a bunch of issues.
        std::list<Frame>::iterator j = m_frames.begin(); 
        for( int i = 0; i < frameNum; i++ )
        {
          j++;
        }
        return *j;
      } 

      virtual ~AnimSequence() {}

     private:

      std::list<Frame> m_frames;

  }; // AnimSequence

} // visualizer

#endif // ANIMSEQUENCE_H
