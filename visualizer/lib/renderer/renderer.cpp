#include "renderer.h"
#include "../selectionrender/selectionrender.h"
#include "../goc_owner.h"
#include <sstream>
#include "../gocfamily_talk.h"
using namespace std;

namespace visualizer
{

  _Renderer *Renderer = 0;

  bool _Renderer::resize(const unsigned int & width, const unsigned int & height, const unsigned int & depth)
  {
    unsigned int _height = height?height:1;

    glViewport( 0, 0, (GLint)width, (GLint)_height);

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
    glScalef( height()/mapSize, height()/mapSize, 1 );

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

    if (!Renderer->clear())
      THROW( Exception, "FILL IN EXCEPTION DETAILS HERE" );

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

    unsigned int rwidth = width();
    unsigned int rheight = height();
    unsigned int rdepth = depth();

    /// @TODO Move this to the appropriate spot
    glShadeModel( GL_SMOOTH );
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    glClearDepth( 1.0f );

    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LEQUAL );

    m_isSetup = true;

    glDisable( GL_TEXTURE_2D );
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    refresh();

    TimeManager->requestUpdate( Renderer );

    if( !m_isSetup )
    {
      THROW( Exception, "Renderer Didn't Set Up Properly" );
    }

  }


  bool _Renderer::isSetup()
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


  bool _Renderer::deleteConstantObj( const unsigned int& id )
  {
    return false;
  }


  unsigned int _Renderer::width()
  {
    if (isSetup())
      return m_width;

    return 0;
  }


  unsigned int _Renderer::height()
  {
    if (isSetup())
      return m_height;

    return 0;
  }


  unsigned int _Renderer::depth()
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


  bool _Renderer::update(const unsigned int & turn, const unsigned int & frame)
  {
    Stats globalTotal, globalP0, globalP1, globalP2, globalP3;
    Stats selectedTotal, selectedP0, selectedP1, selectedP2, selectedP3;
    int health;

    typedef std::map<ObjIdType,LookupNode<GameObject*,ObjIdType>* > Bucket;
    Bucket * bucket = ObjectManager->getBucket(turn,frame);

    if (!bucket)
    {
      //std::cout << "Bucket Requested at (" << turn <<","<<frame << ") does not exist\n";
      return false;
    }

    //  m_renderList.clear();

    bool selectUpdate = SelectionRender->getUpdated();
    float mapSize = (float)OptionsMan->getInt("mapSize");
    float unitSize  = height()/mapSize;

    int x1 = 0;
    int x2 = 0;
    int y1 = 0;
    int y2 = 0;

    return true;
  }


  void _Renderer::setColor
    (
    const float& r,
    const float& g, 
    const float& b,
    const float& a
    ) const
  {
    glColor4f( r, g, b, a );
  
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
    
  }

} // visualizer

