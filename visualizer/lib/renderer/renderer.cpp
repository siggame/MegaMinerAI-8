#include "renderer.h"
#include "../selectionrender/selectionrender.h"
#include "../goc_owner.h"
#include <sstream>
#include "../gocfamily_talk.h"
#include "../common.h"
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

    std::map<int, renderObj*>::iterator it = m_renderConstant.begin();

    for( ; it != m_renderConstant.end(); it++ )
    {
      GOCFamily_Render *r = (GOCFamily_Render*)it->second->getGOC( "RenderFamily" );
      if( r )
      {
        r->renderAt( TimeManager->getTurn(), 0 );
      }
    }

    glPushMatrix();
    float mapSize = (float)OptionsMan->getInt("mapSize");
    glScalef( height()/mapSize, height()/mapSize, 1 );

    if( m_frames )
    {
      cout << m_frames->size() << endl;
      // Check to make sure the game is still loaded;
    }


    #if 0
    typename std::vector<DupObject*>::iterator renderIt = m_renderList.begin();
    for (; renderIt != m_renderList.end(); renderIt++)
    {
      glPushMatrix();
      (*renderIt)->render();
      glPopMatrix();
    }
    #endif

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

    /// @TODO: Move this to the appropriate spot
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


  void _Renderer::registerFrameContainer( std::vector<std::list<SmartPointer<Animatable> > >* frameList )
  {
    // Do we want to delete m_frames?
    // Probably not. 
    m_frames = frameList;

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
    int time = TimeManager->timeHash();

    bool selectUpdate = SelectionRender->getUpdated();
    float mapSize = (float)OptionsMan->getInt("mapSize");
    float unitSize  = height()/mapSize;



    int x1 = 0;
    int x2 = 0;
    int y1 = 0;
    int y2 = 0;

    #if 0
    if( selectUpdate )
    {

      x1 = SelectionRender->getX1()/unitSize;
      x2 = SelectionRender->getX2()/unitSize;
      if( x2 < x1 )
      {
        int temp;
        temp = x2;
        x2 = x1;
        x1 = temp;
      }

      y1 = SelectionRender->getY1()/unitSize;
      y2 = SelectionRender->getY2()/unitSize;

      if( y2 < y1 )
      {
        int temp;
        temp = y1;
        y1 = y2;
        y2 = temp;
      }

      selectedUnitIds.clear();
    }

    Bucket::iterator it = bucket->begin();
    for (;it != bucket->end(); it++)
    {
      int owner = 0;
      if (it->second)
      {
        DupObject temp;
        setDupObj(it->second->data,temp);
        GOComponent * goc = it->second->data->getGOC( "Owner" );
        if( goc )
        {
          owner = ((GOC_Owner*)goc)->owner();
        }
        goc = it->second->data->getGOC("LocationFamily");
        if (goc)
        {
          GOCFamily_Location * loc = (GOCFamily_Location *)(goc);

          if( selectUpdate )
          {
            if( loc->x() >= x1 &&
              loc->x() <= x2 &&
              loc->y() >= y1 &&
              loc->y() <= y2 )
            {
              temp.selected = true;

              #if 1
              int id = it->first;
              selectedUnitIds.insert( id );
              #endif
            } else
            {
              temp.selected = false;
            }
          }

          goc = it->second->data->getGOC( "HealthFamily" );
          if( goc )
          {
            health = ((GOCFamily_Health*)goc)->currentHealth();
          }

          Stats tStats;            //temporary variable for summing the stats
          goc = it->second->data->getGOC( "ObjectType" );
          bool treasure = false;
          if( goc )
          {
            switch( ((ObjectType*)goc)->type() )
            {
              case POT_PIRATE:
                tStats.avgPirateHealth = health;

                tStats.pirates = 1;
                goc = it->second->data->getGOC( "Gold" );
                tStats.gold = ((Gold*)goc)->gold();
                break;
              case POT_SHIP:
                tStats.avgShipHealth = health;
                tStats.ships = 1;
                goc = it->second->data->getGOC( "Gold" );
                tStats.gold = ((Gold*)goc)->gold();
                break;
              case POT_PORT:
                tStats.ports = 1;
                break;
              case POT_TREAS:
                treasure = true;
                tStats.treasures = 1;
                goc = it->second->data->getGOC( "Gold" );
                tStats.gold = ((Gold*)goc)->gold();
                break;
              default:
                break;
            }
          }

          if( selectedUnitIds.find( it->first ) != selectedUnitIds.end() )
          {
            temp.selected = true;
          }
          else
          {
            temp.selected = false;
          }

          if( temp.selected )
          {
            if( !treasure )        //Is Pirate or Ship, check for owner
            {
              switch( owner )
              {
                case 0:
                  selectedP0 += tStats;
                  break;
                case 1:
                  selectedP1 += tStats;
                  break;
                case 2:
                  selectedP2 += tStats;
                  break;
                case 3:
                  selectedP3 += tStats;
                  break;
              }

              //Add anything selected pirate is saying to the console
              goc = it->second->data->getGOC( "TalkFamily" );
              if( goc )
              {
                appendToConsole( ((GOCFamily_Talk*)goc)->message() );
              }

            }                      //Is treasure; buried treasure has no owner
            else
            {
              selectedTotal += tStats;
            }

          }                        //Not selected, add to global
          else
          {

            if( !treasure )        //Is Pirate or Ship, check for owner
            {
              switch( owner )
              {
                case 0:
                  globalP0 += tStats;
                  break;
                case 1:
                  globalP1 += tStats;
                  break;
                case 2:
                  globalP2 += tStats;
                  break;
                case 3:
                  globalP3 += tStats;
                  break;
              }

            }                      //Is treasure; buried treasure has no owner
            else
            {
              globalTotal += tStats;
            }

          }                        //Global only, not selected

          updateLocation(loc->x(),loc->y(),loc->z(),loc->dir(),time,temp);

        }
        else
        {
          std::cout << "no location for obj type: " << temp.objType << '\n';
        }

      }                            //if it->second

    }                              //for Bucket

    //Total selected
    selectedTotal += selectedP0;
    selectedTotal += selectedP1;
    selectedTotal += selectedP2;
    selectedTotal += selectedP3;

    //Total global (add selected to unselected)
    globalP0 += selectedP0;
    globalP1 += selectedP1;
    globalP2 += selectedP2;
    globalP3 += selectedP3;

    globalTotal += selectedTotal;

    selectedP0.final();
    selectedP1.final();
    selectedP2.final();
    selectedP3.final();
    selectedTotal.final();

    globalP0.final();
    globalP1.final();
    globalP2.final();
    globalP3.final();
    globalTotal.final();

    globalStatColumnPopulate (globalTotal, 0);
    globalStatColumnPopulate (globalP0, 1);
    globalStatColumnPopulate (globalP1, 2);
    globalStatColumnPopulate (globalP2, 3);
    globalStatColumnPopulate (globalP3, 4);

    selectionStatColumnPopulate (selectedTotal, 0);
    selectionStatColumnPopulate (selectedP0, 1);
    selectionStatColumnPopulate (selectedP1, 2);
    selectionStatColumnPopulate (selectedP2, 3);
    selectionStatColumnPopulate (selectedP3, 4);
    #endif

    return true;
  }


#if 0
  void _Renderer::printToTable( QTableWidget *w, int c, int r, QString str )
  {
    if( w->itemAt( c, r ) )
    {
      w->itemAt( c, r )->setText( str );
    }
    else
    {
      w->setItem( c, r, new QTableWidgetItem( str ) );
    }

  }


  void _Renderer::printIndividuals( int c, int r, QString str )
  {
    printToTable( GUI::getIndividualStats(), c, r, str );
  }


  void _Renderer::printSelectedStats( int r, int c, QString str )
  {
    printToTable( GUI::getSelectionStats(), c, r, str );
  }


  void _Renderer::printGlobalStats( int r, int c, QString str )
  {
    printToTable( GUI::getGlobalStats(), c, r, str );
  }


  void _Renderer::appendToConsole( string str )
  {
    GUI::appendConsole( str );
  }


  void _Renderer::individualStatColumnPopulate (int id, DupObject unit, int column)
  {
    printIndividuals( column, 1, QString::number(id));
    printIndividuals( column, 2, QString::number(unit.owner));
    printIndividuals( column, 3, QString::number(unit.objType));
    printIndividuals( column, 4, QString::number(unit.health));
    printIndividuals( column, 5, QString::number(unit.gold));
    printIndividuals( column, 6, QString::number(unit.x));
    printIndividuals( column, 7, QString::number(unit.y));
  }


  void _Renderer::selectionStatColumnPopulate (Stats multi, int column)
  {
    printSelectedStats( column, 1, QString::number(multi.pirates));
    printSelectedStats( column, 2, QString::number(multi.avgPirateHealth));
    printSelectedStats( column, 3, QString::number(multi.avgPirateGold));
    printSelectedStats( column, 4, QString::number(multi.gold));
    printSelectedStats( column, 5, QString::number(multi.ships));
    printSelectedStats( column, 6, QString::number(multi.avgShipHealth));
    printSelectedStats( column, 7, QString::number(multi.avgShipGold));
    printSelectedStats( column, 8, QString::number(multi.treasures));
    //printSelectedStats( column, 0, QString::number(0));
  }


  void _Renderer::globalStatColumnPopulate (Stats multi, int column)
  {
    printGlobalStats( column, 1, QString::number(multi.pirates));
    printGlobalStats( column, 2, QString::number(multi.avgPirateHealth));
    printGlobalStats( column, 3, QString::number(multi.avgPirateGold));
    printGlobalStats( column, 4, QString::number(multi.gold));
    printGlobalStats( column, 5, QString::number(multi.ships));
    printGlobalStats( column, 6, QString::number(multi.avgShipHealth));
    printGlobalStats( column, 7, QString::number(multi.avgShipGold));
    printGlobalStats( column, 8, QString::number(multi.treasures));
    //printGlobalStats( column, 0, QString::number(0));
  }


  void _Renderer::setNumIndividuals( int num )
  {
    GUI::getIndividualStats()->setColumnCount(num);
  }
#endif

} // visualizer

