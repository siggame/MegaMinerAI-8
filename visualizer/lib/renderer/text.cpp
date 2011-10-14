#include "text.h"
#include "resourcemanager/resourceman.h"
#include <iostream>
#include <fstream>
#include <QtOpenGL>

using namespace std;

namespace visualizer
{

  Text::Text( const std::string& resource, const std::string& fontWidthsFile )
  {
    ifstream fin( fontWidthsFile.c_str() );

    if( !fin.is_open() )
      return;

    for( size_t i = 0; i < 256; i++ )
    {
      unsigned char temp;
      fin.read( (char*)&temp, sizeof( char ) );
      m_width[ i ] = temp;
      fin.read( (char*)&temp, sizeof( char ) );
    }
    
    m_resource = resource;

  } // Text::Text()

  void Text::drawLeft( const std::string& line ) const
  {
    // At this point, the text should already be translated to the 
    // correct position.
    glPushMatrix();
    float off = 1.0f/16.0f;
    const float defaultSize = 0.25;

    glEnable( GL_BLEND );    
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glDisable( GL_DEPTH_TEST );
    glEnable( GL_TEXTURE_2D );

    ResTexture *r = (ResTexture*)ResourceMan->reference( m_resource, "text" );

    glBindTexture( GL_TEXTURE_2D, r->getTexture() );

    for( size_t i = 0; i < line.size(); i++ )
    {
      size_t c = line[ i ];
      float x = ((float)(c%16)/16.0f);
      float y = ((float)((int)c/16)/16.0f);

      glBegin( GL_QUADS );

        glTexCoord2f( x, y-off );
        glVertex3f( 0, defaultSize, 0 );
        glTexCoord2f( x+off, y-off );
        glVertex3f( defaultSize, defaultSize, 0 );
        glTexCoord2f( x+off, y );
        glVertex3f( defaultSize, 0, 0 );
        glTexCoord2f( x, y );
        glVertex3f( 0, 0, 0 );

      glEnd();

    }

    ResourceMan->release( m_resource, "text" );
    glDisable( GL_TEXTURE_2D );
    glDisable( GL_BLEND );

    glPopMatrix();


  } // Text::drawLeft()

  void Text::drawCenter( const std::string& line ) const
  {
    size_t width = getLineWidth( line )/2;
    glTranslatef( -width, 0, 0 );


  } // Text::drawCenter()

  void Text::drawRight( const std::string& line ) const
  {
    size_t width = getLineWidth( line );
    glTranslatef( -width, 0, 0 );

  } // Text::drawRight()

  size_t Text::getLineWidth( const std::string& line ) const
  {
    size_t width = 0;
    for( size_t i = 0; i < line.size(); i++ )
    {
      width += m_width[ line[ i ] ];
    }

    return width;

  } // Text::getLineWidth()

  const Text& Text::operator << ( const std::string& line ) const
  {
    drawLeft( line );
    glTranslatef( getLineWidth( line ), 0, 0 );
    return *this;
  } // Text::operator << 

} // visualizer
