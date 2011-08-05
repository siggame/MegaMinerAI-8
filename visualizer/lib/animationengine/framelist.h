#ifndef FRAMELIST_H
#define FRAMELIST_H

#include "frame.h"

namespace visualizer
{

  class FrameLine
  {
    public:
      void addFrame( const Frame& frame );
      const size_t size() const;

    private:
      std::list<Frame> m_frames;


  }; // FrameLine

} // visualizer

#endif // FRAMELIST_H
