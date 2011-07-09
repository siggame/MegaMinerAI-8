#include "renderer.h"
#include "../selectionrender/selectionrender.h"
#include "../goc_owner.h"
#include <sstream>
#include "../gocfamily_talk.h"
using namespace std;

// TODO: REMOVE LATER FOR NON_GAME SPECIFIC
#include "../../piracy/objecttype.h"
#include "../../piracy/piratehealth.h"
#include "../../piracy/shiphealth.h"
#include "../../piracy/gold.h"


/** @brief resize
 * resize and refresh the projection  and modelview matricies
 * @param width the x size of the render area.
 * @param height the y size of the render area.
 * @param depth the z depth of the render area. default 10
 * @return true if successful resize
 */
bool Renderer::resize(const unsigned int & width, const unsigned int & height, const unsigned int & depth)
{
#if 0
  if (!Single::isInit())
    return false;
#endif

  unsigned int _height = height?height:1;

  glViewport( 0, 0, (GLint)width, (GLint)_height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho( 0, width,_height,0, -depth, depth );

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  Single::instance()->m_height = _height;
  Single::instance()->m_width = width;
  Single::instance()->m_depth = depth;
  refresh();
  return true;
}


/** @brief refresh
 *	draw objects on screen
 * @return true if successful
 */
bool Renderer::refresh()
{
#if 0
  if (!Single::isInit())
    return false;
#endif

  if (!isSetup())
    return false;

  if( SelectionRender::instance()->getUpdated() )
  {
    update( TimeManager.getTurn(), 0 );
  }

  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  std::map<int, renderObj*>::iterator it = Single::instance()->m_renderConstant.begin();

  for( ; it != Single::instance()->m_renderConstant.end(); it++ )
  {
    GOCFamily_Render *r = (GOCFamily_Render*)it->second->getGOC( "RenderFamily" );
    if( r )
    {
      r->renderAt( TimeManager.getTurn(), 0 );
    }
  }

  glPushMatrix();
  float mapSize = (float)OptionsMan::getInt("mapSize");
  glScalef( height()/mapSize, height()/mapSize, 1 );

#if 0
  typename std::vector<DupObject*>::iterator renderIt = Single::instance()->m_renderList.begin();
  for (; renderIt != Single::instance()->m_renderList.end(); renderIt++)
  {
    glPushMatrix();
    (*renderIt)->render();
    glPopMatrix();
  }
#endif

  glPopMatrix();

  if( Single::instance()->m_parent )
  {
    Single::instance()->m_parent->swapBuffers();
  }

  SelectionRender::instance()->setUpdated(false);

  return true;
}


void Renderer::setParent( RenderWidget *parent )
{
#if 0
  if (!Single::isInit())
    return;                      //! @todo throw error
#endif
  Single::instance()->m_parent = parent;
}


/** @brief destroy
 * destroy the singleton
 * @return true on success
 */
bool Renderer::destroy()
{
#if 0
  if(!Single::isInit())
    return false;
#endif
  if (!clear())
    return false;

  return Renderer::destroy();
}


/** @brief create
 * create the singleton and setup the render area
 * @return true on success
 */
bool Renderer::create()
{
#if 0
  if (!Single::create())
    return false;
#endif

  Single::instance()->m_parent = 0;
  Single::instance()->m_height = 0;
  Single::instance()->m_width  = 0;
  Single::instance()->m_depth  = 10;
  //Single::instance()->m_dupListDirs = 0;
  //Single::instance()-> m_duplicateList = NULL;

  return true;
}


/** @brief getRenderObject
 * get the render object associated with the id
 * @param id the GO ID of the render object
 * @return a pointer to the render object
 * @todo figure out if we want multiple render objects to a single game object
 *//*
renderObj* Renderer::getRenderObject(const unsigned int id)
{
  if (!isInit())
    return NULL;

  if (instance()->m_objects.find(id) == instance()->m_objects.end())
    return NULL;

  return instance()->m_objects[id];
}*/

/** @brief setup
 * setup the rendering for the render, size the screen according to
 *	the width and height given
 * @return true if successful
 * @todo add more to the render setup
 */
bool Renderer::setup()
{
#if 0
  if (!Single::isInit())
  {
    std::cout << "Renderer Error: Trying to set up an uninitialized Renderer\n";
    return false;
  }
#endif

  /** @todo fill this in with more setup information */
  if ( Single::instance()->m_width && Single::instance()->m_height && Single::instance()->m_depth )
  {
    resize( Single::instance()->m_width, Single::instance()->m_height, Single::instance()->m_depth );
  }
  else if ( Single::instance()->m_width && Single::instance()->m_height )
  {
    resize( Single::instance()->m_width, Single::instance()->m_height );
  }
  else
  {
    if ( OptionsMan::exists(renderHeightName) && OptionsMan::optionType(renderDepthName) == OT_INT &&
      OptionsMan::exists(renderWidthName) && OptionsMan::optionType(renderWidthName) == OT_INT )
    {
      if ( OptionsMan::exists(renderDepthName) && OptionsMan::optionType(renderDepthName) == OT_INT)
      {
        resize( OptionsMan::getInt(renderWidthName),
          OptionsMan::getInt(renderHeightName),
          OptionsMan::getInt(renderDepthName) );
      }
      else
      {
        resize( OptionsMan::getInt(renderWidthName),
          OptionsMan::getInt(renderHeightName) );
      }
    }
  }

  clear();

  unsigned int rwidth = width();
  unsigned int rheight = height();
  unsigned int rdepth = depth();

  std::cout << "Renderer width: " << rwidth << " height: " << rheight << " depth: " << rdepth << '\n';

#if 0
  if (Single::instance()->m_dupListDirs)
  {
    Single::instance()->m_duplicateList = new DupObject***[rwidth];
    for (unsigned int x = 0; x < width(); x++)
    {
      Single::instance()->m_duplicateList[x] = new DupObject**[rheight];
      for (unsigned int y = 0; y < height(); y++)
      {
        Single::instance()->m_duplicateList[x][y] = new DupObject*[rdepth];
        for (unsigned int z = 0; z < rdepth; z++)
        {
          Single::instance()->m_duplicateList[x][y][z] = new DupObject[Single::instance()->m_dupListDirs];
        }
      }
    }
  }
  else if (OptionsMan::exists(renderDirsName) && OptionsMan::optionType(renderDirsName) == OT_INT)
  {
    Single::instance()->m_dupListDirs = OptionsMan::getInt(renderDirsName);
    Single::instance()->m_duplicateList = new DupObject***[width()];
    for (unsigned int x = 0; x < width(); x++)
    {
      Single::instance()->m_duplicateList[x] = new DupObject**[height()];
      for (unsigned int y = 0; y < height(); y++)
      {
        Single::instance()->m_duplicateList[x][y] = new DupObject*[depth()];
        for (unsigned int z = 0; z < depth(); z++)
        {
          Single::instance()->m_duplicateList[x][y][z] = new DupObject[Single::instance()->m_dupListDirs];
        }
      }
    }
  }
  else
  {
    Single::instance()->m_duplicateList = new DupObject***[width()];
    for (unsigned int x = 0; x < width(); x++)
    {
      Single::instance()->m_duplicateList[x] = new DupObject**[height()];
      for (unsigned int y = 0; y < height(); y++)
      {
        Single::instance()->m_duplicateList[x][y] = new DupObject*[depth()];
        for (unsigned int z = 0; z < depth(); z++)
        {
          Single::instance()->m_duplicateList[x][y][z] = new DupObject[1];
        }
      }
    }
    Single::instance()->m_dupListDirs = 1;
  }
#endif

  /// @TODO: Move this to the appropriate spot
  glShadeModel( GL_SMOOTH );
  glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
  glClearDepth( 1.0f );

  glEnable( GL_DEPTH_TEST );
  glDepthFunc( GL_LEQUAL );

  Single::instance()->m_isSetup = true;

  glDisable( GL_TEXTURE_2D );
  glEnable( GL_BLEND );
  glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

  refresh();

  TimeManager.requestUpdate( Singleton<Renderer>::instance()  );

  return Single::instance()->m_isSetup;
}


/** @brief isSetup
 * access if the module has been set up
 * @return true if set up
 */
bool Renderer::isSetup()
{
#if 0
  if (!Single::isInit())
    return false;
#endif

  return Renderer::instance()->m_isSetup;
}


/** @brief clear
 * clear all references to render objects
 * @return true on success
 */
bool Renderer::clear()
{
#if 0
  if (!Single::isInit())
    return false;
#endif

  //Single::instance()->m_duplicateList = NULL;

  std::map<int, renderObj*>::iterator it = Single::instance()->m_renderConstant.begin();
  for(; it!=Single::instance()->m_renderConstant.end(); it++ )
  {
    delete (it->second);
  }

  Single::instance()->m_renderConstant.clear();

  return true;
}

bool Renderer::registerConstantObj( const unsigned int& id, renderObj* obj )
{
#if 0
  if (!Single::isInit())
  {
    return false;
  }
#endif

  if( Single::instance()->m_renderConstant.find( id ) != Single::instance()->m_renderConstant.end() )
  {
    return false;
    delete Single::instance()->m_renderConstant[id];
  }

  Single::instance()->m_renderConstant[id] = obj;

  return true;
}


bool Renderer::deleteConstantObj( const unsigned int& id )
{
#if 0
  std::map<int,renderObj*> it = Single::instance()->m_renderConstant.find( id );
  if( it != Single::instance()->m_renderConstant.end() )
  {
    delete Single::instance()->m_renderConstant[id];
    Single::instance()->m_renderConstant.erase( it );
    return true;
  } else
  {
    return false;
  }
#endif
  return false;
}


#if 0
/** @brief updateLocation
 *
 * @todo: document this function
 */
void Renderer::updateLocation(const unsigned int & x, const unsigned int & y, const unsigned int & z, const unsigned int & dir, const unsigned int & time, DupObject obj)
{
  //std::cout << "updateLocation Called\n";

  if (!Single::isInit())
    return;

  if (!isSetup())
    return;

  if (x > width() || y > height() || z > depth() || dir > Single::instance()->m_dupListDirs)
    return;                      //! @todo throw an error

  bool sameFlag = false;

  if (obj.time == time)
  {
    sameFlag = true;
  }

  obj.x = x;
  obj.y = y;

  obj.time = time;
  Single::instance()->m_duplicateList[x][y][z][dir] += obj;

  if (!sameFlag)
  {
    Single::instance()->m_renderList.push_back(&(Single::instance()->m_duplicateList[x][y][z][dir]));
    //std::cout << "Gets to add\n";
  }
}
#endif


/**
 * @todo doxyment
 */
unsigned int Renderer::width()
{
  if (isSetup())
    return Single::instance()->m_width;

  return 0;
}


/**
 * @todo doxyment
 */
unsigned int Renderer::height()
{
  if (isSetup())
    return Single::instance()->m_height;

  return 0;
}


/**
 * @todo doxyment
 */
unsigned int Renderer::depth()
{
  if (isSetup())
    return Single::instance()->m_depth;

  return 0;
}

void Renderer::update()
{
  Renderer::refresh();
  Renderer::update( TimeManager.getTurn(), 0 );
}


/**
 * @todo doxyment
 */
bool Renderer::update(const unsigned int & turn, const unsigned int & frame)
{
  Stats globalTotal, globalP0, globalP1, globalP2, globalP3; 
  Stats selectedTotal, selectedP0, selectedP1, selectedP2, selectedP3; 
  int health;

#if 0
  if (!Single::isInit())
  {
    std::cout << "Update Failed: Renderer is not inititalized or setup\n";
    return false;
  }                              //! @todo fuck off
#endif

  typedef std::map<ObjIdType,LookupNode<GameObject*,ObjIdType>* > Bucket;
  Bucket * bucket = ObjectManager::getBucket(turn,frame);

  if (!bucket)
  {
    std::cout << "Bucket Requested at (" << turn <<","<<frame << ") does not exist\n";
    return false;
  }

//  Single::instance()->m_renderList.clear();
  int time = TimeManager.timeHash();

  bool selectUpdate = SelectionRender::instance()->getUpdated();
  float mapSize = (float)OptionsMan::getInt("mapSize");
  float unitSize  = height()/mapSize;

  int x1 = 0;
  int x2 = 0;
  int y1 = 0;
  int y2 = 0;

#if 0
  if( selectUpdate )
  {

    x1 = SelectionRender::instance()->getX1()/unitSize;
    x2 = SelectionRender::instance()->getX2()/unitSize;
    if( x2 < x1 )
    {
      int temp;
      temp = x2;
      x2 = x1;
      x1 = temp;
    }

    y1 = SelectionRender::instance()->getY1()/unitSize;
    y2 = SelectionRender::instance()->getY2()/unitSize;

    if( y2 < y1 )
    {
      int temp;
      temp = y1;
      y1 = y2;
      y2 = temp;
    }
  
    Single::instance()->selectedUnitIds.clear();
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
            Single::instance()->selectedUnitIds.insert( id );
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

        Stats tStats; //temporary variable for summing the stats
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


        if( Single::instance()->selectedUnitIds.find( it->first ) != Single::instance()->selectedUnitIds.end() )
        {
          temp.selected = true;
        }
        else
        {
          temp.selected = false;
        }

        if( temp.selected )
        {
          if( !treasure ) //Is Pirate or Ship, check for owner
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
              Single::instance()->appendToConsole( ((GOCFamily_Talk*)goc)->message() );
            }
            
          } else { //Is treasure; buried treasure has no owner
            selectedTotal += tStats;
          }
          
        } else { //Not selected, add to global
        
          if( !treasure ) //Is Pirate or Ship, check for owner
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
              
            } else { //Is treasure; buried treasure has no owner
              globalTotal += tStats;
            }

        }//Global only, not selected


        updateLocation(loc->x(),loc->y(),loc->z(),loc->dir(),time,temp);

      }
      else
      {
        std::cout << "no location for obj type: " << temp.objType << '\n';
      }

    }//if it->second

  }//for Bucket

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

  Single::instance()->globalStatColumnPopulate (globalTotal, 0);
  Single::instance()->globalStatColumnPopulate (globalP0, 1);
  Single::instance()->globalStatColumnPopulate (globalP1, 2);
  Single::instance()->globalStatColumnPopulate (globalP2, 3);
  Single::instance()->globalStatColumnPopulate (globalP3, 4);

  Single::instance()->selectionStatColumnPopulate (selectedTotal, 0);
  Single::instance()->selectionStatColumnPopulate (selectedP0, 1);
  Single::instance()->selectionStatColumnPopulate (selectedP1, 2);
  Single::instance()->selectionStatColumnPopulate (selectedP2, 3);
  Single::instance()->selectionStatColumnPopulate (selectedP3, 4);
#endif
  
  return true;
}

#if 0
void Renderer::printToTable( QTableWidget *w, int c, int r, QString str )
{
  if( w->itemAt( c, r ) )
  {
    w->itemAt( c, r )->setText( str );
  } else {
    w->setItem( c, r, new QTableWidgetItem( str ) );
  }

}

void Renderer::printIndividuals( int c, int r, QString str )
{
  printToTable( GUI::getIndividualStats(), c, r, str );
}

void Renderer::printSelectedStats( int r, int c, QString str )
{
  printToTable( GUI::getSelectionStats(), c, r, str );
}

void Renderer::printGlobalStats( int r, int c, QString str )
{
  printToTable( GUI::getGlobalStats(), c, r, str );
}

void Renderer::appendToConsole( string str )
{
  GUI::appendConsole( str );
}

void Renderer::individualStatColumnPopulate (int id, DupObject unit, int column)
{
  Single::instance()->printIndividuals( column, 1, QString::number(id));
  Single::instance()->printIndividuals( column, 2, QString::number(unit.owner));
  Single::instance()->printIndividuals( column, 3, QString::number(unit.objType));
  Single::instance()->printIndividuals( column, 4, QString::number(unit.health));
  Single::instance()->printIndividuals( column, 5, QString::number(unit.gold));
  Single::instance()->printIndividuals( column, 6, QString::number(unit.x));
  Single::instance()->printIndividuals( column, 7, QString::number(unit.y));
}

void Renderer::selectionStatColumnPopulate (Stats multi, int column)
{
  Single::instance()->printSelectedStats( column, 1, QString::number(multi.pirates));
  Single::instance()->printSelectedStats( column, 2, QString::number(multi.avgPirateHealth));
  Single::instance()->printSelectedStats( column, 3, QString::number(multi.avgPirateGold));
  Single::instance()->printSelectedStats( column, 4, QString::number(multi.gold));
  Single::instance()->printSelectedStats( column, 5, QString::number(multi.ships));
  Single::instance()->printSelectedStats( column, 6, QString::number(multi.avgShipHealth));
  Single::instance()->printSelectedStats( column, 7, QString::number(multi.avgShipGold));
  Single::instance()->printSelectedStats( column, 8, QString::number(multi.treasures));
  //Single::instance()->printSelectedStats( column, 0, QString::number(0));
}

void Renderer::globalStatColumnPopulate (Stats multi, int column)
{
  Single::instance()->printGlobalStats( column, 1, QString::number(multi.pirates));
  Single::instance()->printGlobalStats( column, 2, QString::number(multi.avgPirateHealth));
  Single::instance()->printGlobalStats( column, 3, QString::number(multi.avgPirateGold));
  Single::instance()->printGlobalStats( column, 4, QString::number(multi.gold));
  Single::instance()->printGlobalStats( column, 5, QString::number(multi.ships));
  Single::instance()->printGlobalStats( column, 6, QString::number(multi.avgShipHealth));
  Single::instance()->printGlobalStats( column, 7, QString::number(multi.avgShipGold));
  Single::instance()->printGlobalStats( column, 8, QString::number(multi.treasures));
  //Single::instance()->printGlobalStats( column, 0, QString::number(0));
}

void Renderer::setNumIndividuals( int num )
{
  GUI::getIndividualStats()->setColumnCount(num);
}
#endif

