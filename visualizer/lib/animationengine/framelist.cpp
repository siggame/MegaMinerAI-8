#include "framelist.h"

namespace visualizer
{

  void FrameLine::addFrame( const Frame& frame )
  {
    m_frames.push_back( frame );

  } // FrameLine::addFrame()

  const size_t FrameLine::size() const
  {
    return m_frames.size();
  } // FrameLine::size()

} // visualizer
