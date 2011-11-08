#ifndef TEXT_H
#define TEXT_H

#include <string>

namespace visualizer
{
  class Text
  {
    public:
      Text( const std::string& resource, const std::string& fontWidthsFile );

      const Text& operator << ( const std::string& line ) const;

      void drawLeft( const std::string& line ) const;
      void drawRight( const std::string& line ) const;
      void drawCenter( const std::string& line ) const;

    private:
      size_t getLineWidth( const std::string& line ) const;
      size_t getCharWidth( const size_t& c ) const;
      
      unsigned char m_width[256];
      std::string m_resource;
      unsigned int m_list;

  };


} // visualizer


#endif // TEXT_H
