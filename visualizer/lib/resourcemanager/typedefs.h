#ifndef TYPEDEFS_H
#define TYPEDEFS_H

namespace visualizer
{

  enum ResourceType
  {
    RT_NONE, 
    RT_TEXTURE, 
    RT_ANIMATION, 
    RS_FONT,
    RT_DISPLAY_LIST
  };

  typedef std::string ResID_t;

} // visualizer

#endif
