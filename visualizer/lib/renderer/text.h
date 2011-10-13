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

      void drawLeft( const std::string& line );
      void drawRight( const std::string& line );
      void drawCenter( const std::string& line );

    private:
      size_t getLineWidth( const std::string& line );
      
      unsigned char m_width[256];
      std::string m_resource;

  };


} // visualizer


#endif // TEXT_H
