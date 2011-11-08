#include "text.h"
#include "resourcemanager/resourceman.h"
#include <iostream>
#include <fstream>
#include <QtOpenGL>

using namespace std;

namespace visualizer
{

  const float defaultSize = 0.25;
  const float widthMultiplier = 0.5f;
  const float off = 1.0f/16.0f;
  Text::Text( const std::string& resource, const std::string& fontWidthsFile )
  {
    ifstream fin( fontWidthsFile.c_str() );

    if( !fin.is_open() )
      return;

    m_list = glGenLists( 256 );

    for( size_t i = 0; i < 256; i++ )
    {
      unsigned char temp;
      fin.read( (char*)&temp, sizeof( char ) );
      m_width[ i ] = temp;
      m_width[ i ] = m_width[ i ]/1.75;

      glNewList( m_list+i, GL_COMPILE );
        
        float x = 1-((float)(i%16)/16.0f)-off;
        float y = 1-((float)((int)i/16)/16.0f)+off;

        glBegin( GL_QUADS );
          glTexCoord2f( x+off, y+off );
          glVertex3f( 0, 0, 0 );
          glTexCoord2f( x, y+off );
          glVertex3f( defaultSize, 0, 0 );
          glTexCoord2f( x, y );
          glVertex3f( defaultSize, defaultSize, 0 );
          glTexCoord2f( x+off, y );
          glVertex3f( 0, defaultSize, 0 );
        glEnd();

        float t = (float)getCharWidth( i )/32*defaultSize*widthMultiplier;
        glTranslatef( t, 0, 0 );     

      glEndList();
      
      fin.read( (char*)&temp, sizeof( char ) );
    }
    
    m_resource = resource;

  } // Text::Text()

  void Text::drawLeft( const std::string& line ) const
  {
    // At this point, the text should already be translated to the 
    // correct position.
    glPushMatrix();

    glEnable( GL_BLEND );    
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glDisable( GL_DEPTH_TEST );
    glEnable( GL_TEXTURE_2D );

    ResTexture *r = (ResTexture*)ResourceMan->reference( m_resource, "text" );

    glBindTexture( GL_TEXTURE_2D, r->getTexture() );

    glListBase( m_list );
    glCallLists( line.size(), GL_UNSIGNED_BYTE, line.c_str() ); 

    ResourceMan->release( m_resource, "text" );
    glDisable( GL_TEXTURE_2D );
    glDisable( GL_BLEND );

    glPopMatrix();


  } // Text::drawLeft()

  void Text::drawCenter( const std::string& line ) const
  {
    glPushMatrix();
    float width = getLineWidth( line )/2;

    width *= defaultSize/32*widthMultiplier;

    glTranslatef( -width, 0, 0 );
    drawLeft( line );
    glPopMatrix();

  } // Text::drawCenter()

  void Text::drawRight( const std::string& line ) const
  {
    glPushMatrix();
    float width = getLineWidth( line );
    width *= defaultSize/32*widthMultiplier;
    glTranslatef( -width, 0, 0 );
    drawLeft( line );
    glPopMatrix();

  } // Text::drawRight()

  size_t Text::getLineWidth( const std::string& line ) const
  {
    size_t width = 0;
    for( size_t i = 0; i < line.size(); i++ )
    {
      width += getCharWidth( line[ i ] );
    }

    return width;

  } // Text::getLineWidth()

  size_t Text::getCharWidth( const size_t& c ) const
  {
    return m_width[ c-32 ];
  }

  const Text& Text::operator << ( const std::string& line ) const
  {
    drawLeft( line );
    glTranslatef( getLineWidth( line ), 0, 0 );
    return *this;
  } // Text::operator << 

} // visualizer
