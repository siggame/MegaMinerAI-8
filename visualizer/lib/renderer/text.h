#ifndef TEXT_H
#define TEXT_H

#include <string>

namespace visualizer
{
  class Text
  {
    public:
      Text();
      Text( const std::string& resource, const std::string& fontWidthsFile );

      Text& operator << ( const std::string& line );

    private:
      unsigned char m_width[256];

      std::string resource;

  };


} // visualizer


#endif // TEXT_H
