#include "renderer.h"
#include "../selectionrender/selectionrender.h"
#include <sstream>
using namespace std;

namespace visualizer
{

  _Renderer *Renderer = 0;

  bool _Renderer::resize(const unsigned int & width, const unsigned int & height, const unsigned int & depth)
  {
    unsigned int _height = height?height:1;

    viewport( 0, 0, width, _height );

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho( 0, width,_height,0, -depth, depth );

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    m_height = _height;
    m_width = width;
    m_depth = depth;
    refresh();
    return true;
  }

  void _Renderer::viewport( int x, int y, int width, int height )
  {
    static int _x = -1;
    static int _y = -1;
    static int _width = -1;
    static int _height = -1;

    if( width != _width || height != _height || x != _x || y != _y )
    {
      glViewport( x, y, width, height );
      _width = width;
      _height = height;
      _x = x;
      _y = y;
    }
  }

  bool _Renderer::refresh()
  {
    if (!isSetup())
      return false;

    if( SelectionRender->getUpdated() )
    {
      update( TimeManager->getTurn(), 0 );
    }

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    /// @TODO Need to clean up this code a bit.
    glPushMatrix();
    float mapSize = (float)OptionsMan->getInt("mapSize");

    translate( width()*m_winX/m_unitSzX, height()*m_winY/m_unitSzY );

    float bigger = height()<width() ? height() : width();

    float factor;

    if( height()/m_unitSzY > width()/m_unitSzX )
    {
      factor = width() / m_unitSzX;
    } else
    {
      factor = height() / m_unitSzY;
    }

    glScalef( factor, factor, 1 );

    AnimationEngine->draw();

    glPopMatrix();

    if( m_parent )
    {
      m_parent->swapBuffers();
    }

    SelectionRender->setUpdated(false);

    return true;
  }


  void _Renderer::setParent( RenderWidget *parent )
  {
    #if 0
    if (!Single::isInit())
      return;                      //! @todo throw error
    #endif
    m_parent = parent;
  }


  void _Renderer::destroy()
  {
    if( !Renderer )
      return;

    if (!Renderer->clear())
      THROW( Exception, "FILL IN EXCEPTION DETAILS HERE" );

    TimeManager->removeRequest( Renderer );

    delete Renderer;
    Renderer = 0;

  }


  bool _Renderer::create()
  {
    m_parent = 0;
    m_height = 0;
    m_width  = 0;
    m_depth  = 10;

    return true;
  }


  void _Renderer::setup()
  {
    if( !Renderer )
    {
      Renderer = new _Renderer;
      SETUP( "Renderer" )
    }
    else
    {
      THROW( Exception, "Renderer Already Initialized" );
    }

    Renderer->_setup();

  }


  void _Renderer::_setup()
  {
    /** @todo fill this in with more setup information */
    if ( m_width && m_height && m_depth )
    {
      resize( m_width, m_height, m_depth );
    }
    else if ( m_width && m_height )
    {
      resize( m_width, m_height );
    }
    else
    {
      if ( OptionsMan->exists(renderHeightName) && OptionsMan->optionType(renderDepthName) == OT_INT &&
        OptionsMan->exists(renderWidthName) && OptionsMan->optionType(renderWidthName) == OT_INT )
      {
        if ( OptionsMan->exists(renderDepthName) && OptionsMan->optionType(renderDepthName) == OT_INT)
        {
          resize( OptionsMan->getInt(renderWidthName),
            OptionsMan->getInt(renderHeightName),
            OptionsMan->getInt(renderDepthName) );
        }
        else
        {
          resize( OptionsMan->getInt(renderWidthName),
            OptionsMan->getInt(renderHeightName) );
        }
      }
    }

    clear();

    glShadeModel( GL_SMOOTH );
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    glClearDepth( 1.0f );

    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LEQUAL );

    glDisable( GL_TEXTURE_2D );
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    refresh();

    TimeManager->requestUpdate( Renderer );

    m_isSetup = true;
      
	}

  bool _Renderer::isSetup() const
  {
    return m_isSetup;
  }


  bool _Renderer::clear()
  {
    std::map<int, renderObj*>::iterator it = m_renderConstant.begin();
    for(; it!=m_renderConstant.end(); it++ )
    {
      delete (it->second);
    }

    m_renderConstant.clear();

    return true;
  }


  bool _Renderer::registerConstantObj( const unsigned int& id, renderObj* obj )
  {
    if( m_renderConstant.find( id ) != m_renderConstant.end() )
    {
      return false;
      delete m_renderConstant[id];
    }

    m_renderConstant[id] = obj;

    return true;
  }


  bool _Renderer::deleteConstantObj( const unsigned int&/* id */ )
  {
    return false;
  }


  unsigned int _Renderer::width() const
  {
    if (isSetup())
      return m_width;

    return 0;
  }


  unsigned int _Renderer::height() const
  {
    if (isSetup())
      return m_height;

    return 0;
  }


  unsigned int _Renderer::depth() const
  {
    if (isSetup())
      return m_depth;

    return 0;
  }

  void _Renderer::update()
  {
    _Renderer::refresh();
    _Renderer::update( TimeManager->getTurn(), 0 );
  }


  bool _Renderer::update(const unsigned int & /*turn*/, const unsigned int & /*frame*/)
  {
#if 0
    bool selectUpdate = SelectionRender->getUpdated();
    float mapSize = (float)OptionsMan->getInt("mapSize");
    float unitSize  = height()/mapSize;

#endif
    return true;
  }


  void _Renderer::setColor
    (
    const Color& c
    ) const
  {
    glColor4f( c.r, c.g, c.b, c.a );
  
  } // _Renderer::setColor()

  void _Renderer::drawQuad
    (
    const float& x,
    const float& y,
    const float& w,
    const float& h,
    const float& z 
    ) const
  {
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
   
    glBegin( GL_QUADS );
      glVertex3f( x, y, z );
      glVertex3f( x+w, y, z );
      glVertex3f( x+w, y+h, z );
      glVertex3f( x, y+h, z );
    glEnd();

    glDisable( GL_BLEND );
    
  } // _Renderer::drawQuad()

  void _Renderer::drawTexturedQuad
    (
    const float& x,
    const float& y,
    const float& w,
    const float& h,
    const std::string& resource,
    const float& z
    ) const
  {
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glDisable( GL_DEPTH_TEST );
    glEnable( GL_TEXTURE_2D );

    ResTexture *r = (ResTexture*)ResourceMan->reference( resource, "renderer" );

    glBindTexture( GL_TEXTURE_2D, r->getTexture() );
    glBegin( GL_QUADS );
      glTexCoord2f( 1, 1 ); glVertex3f( x, y, z );
      glTexCoord2f( 0, 1 ); glVertex3f( x+w, y, z );
      glTexCoord2f( 0, 0 ); glVertex3f( x+w, y+h, z );
      glTexCoord2f( 1, 0 ); glVertex3f( x, y+h, z );
    glEnd();

    ResourceMan->release( resource, "renderer" );
    glDisable( GL_TEXTURE_2D );
    glDisable( GL_BLEND );
    
  } // _Renderer::DrawTexturedQuad()

  void _Renderer::drawAnimQuad
    (
    const float& x,
    const float& y,
    const float& w,
    const float& h,
    const std::string& resource,
    const int& frameNumber,
    const float& z
    ) const
  {
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glDisable( GL_DEPTH_TEST );
    glEnable( GL_TEXTURE_2D );

    ResAnimation *r = (ResAnimation*)ResourceMan->reference( resource, "renderer" );
    Rect texCoord = r->calcTexCoord( frameNumber );

    glBindTexture( GL_TEXTURE_2D, r->getTexture() );
    glBegin( GL_QUADS );
      glTexCoord2f( texCoord.bottomRight.x, texCoord.bottomRight.y ); glVertex3f( x, y, z );
      glTexCoord2f( texCoord.bottomLeft.x, texCoord.bottomLeft.y ); glVertex3f( x+w, y, z );
      glTexCoord2f( texCoord.upLeft.x, texCoord.upLeft.y ); glVertex3f( x+w, y+h, z );
      glTexCoord2f( texCoord.upRight.x, texCoord.upRight.y ); glVertex3f( x, y+h, z );
    glEnd();

    ResourceMan->release( resource, "renderer" );
    glDisable( GL_TEXTURE_2D );
    glDisable( GL_BLEND );
    
  } // _Renderer::drawAnimQuad()

  void _Renderer::translate
    (
    const float& x,
    const float& y,
    const float& z
    ) const
  {
    if( x != 0 || y != 0 || z != 0 )
      glTranslatef( x, y, z );
  } // _Renderer::translate()

  void _Renderer::scale
    (
    const float& x,
    const float& y,
    const float& z
    ) const
  {
    glScalef( x, y, z );
  } // _Renderer::scale()

  void _Renderer::rotate
    (
    const float& amount, 
    const float& x, 
    const float& y, 
    const float& z
    ) const
  {
    glRotatef( amount, x, y, z );
  }

  void _Renderer::drawLine
    (
    const float& sX,
    const float& sY,
    const float& eX,
    const float& eY,
    const float& width
    ) const
  {
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    glLineWidth( width );

    glBegin( GL_LINES );

      glVertex2f( sX, sY );
      glVertex2f( eX, eY );

    glEnd();

    glDisable( GL_BLEND );
  }

  void _Renderer::drawProgressBar
    (
    const float& x,
    const float& y,
    const float& w, 
    const float& h,
    const float& percent,
    const Color& color,
    const float& lineWidth, 
    const float& z
    ) const
  {
    // The percent bar
    glBegin( GL_QUADS );
      glVertex3f( x, y, z );
      glVertex3f( x+w*percent, y, z );
      glVertex3f( x+w*percent, y+h, z );
      glVertex3f( x, y+h, z );
    glEnd();

    glColor4f( color.r, color.g, color.b, color.a );
    glLineWidth( lineWidth );

    glBegin( GL_LINE_STRIP );
      glVertex3f( x, y, z );
      glVertex3f( x+w, y, z );
      glVertex3f( x+w, y+h, z );
      glVertex3f( x, y+h, z );
      glVertex3f( x, y, z );
    glEnd();
  } // _Renderer::DrawProgressBar()

  void _Renderer::drawText
    (
    const float& x,
    const float& y,
    const std::string& fontName,
    const std::string& line,
    const float& size,
    const Alignment& a 
    ) const
  {
    const Text& t = ((ResFont*)ResourceMan->reference( fontName, "renderer" ))->getFont();

    glPushMatrix();
    // Scale to camera stuff. 
    // Then scale proportionally to size
    glTranslatef( x, y, 0 );
    scale( size, size );

    switch( a )
    {
      case Left:
        t.drawLeft( line );
      break;
      case Right:
        t.drawRight( line );
      break;
      case Center:
        t.drawCenter( line );
      break;
    }

    glPopMatrix();

    ResourceMan->release( fontName, "renderer" );
  } // _Renderer::drawText()

  void _Renderer::setCamera
    (
    const float& sX,
    const float& sY,
    const float& eX,
    const float& eY
    )
  { 
    m_winX = sX;
    m_winY = sY;
    m_winW = eX;
    m_winH = eY;

    resize( width(), height() );

  } // _Renderer::setCamera()

  void _Renderer::beginList( const std::string& name ) const
  {
    ResourceMan->newDisplayList( name );
    ResDisplayList* dl = (ResDisplayList*)ResourceMan->reference( name, "renderer" );
    dl->startList();
    ResourceMan->release( name, "renderer" );

  } // _Renderer::beginList()

  void _Renderer::endList( const std::string& name ) const
  {
    ResDisplayList* dl = (ResDisplayList*)ResourceMan->reference( name, "renderer" );
    dl->endList();
    ResourceMan->release( name, "renderer" );

  } // _Renderer::endList()

  void _Renderer::drawList( const std::string& name ) const
  {
    ResDisplayList* dl = (ResDisplayList*)ResourceMan->reference( name, "renderer" );
    dl->draw();
    ResourceMan->release( name, "renderer" );

  } // _Renderer::drawList()

  void _Renderer::push() const
  {
    glPushMatrix();
  } // _Renderer::push()

  void _Renderer::pop() const
  {
    glPopMatrix();
  } // _Renderer::pop()

  void _Renderer::setUnitSize
    (
    const float& sX,
    const float& sY
    )
  {
    m_unitSzX = sX;
    m_unitSzY = sY;

    refresh();
  } // _Renderer::setUnitSize()

} // visualizer

