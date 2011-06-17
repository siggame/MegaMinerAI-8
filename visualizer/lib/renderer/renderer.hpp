#ifndef RENDERER_HPP
#define RENDERER_HPP

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
template <typename DupObject>
bool Renderer<DupObject>::resize(const unsigned int & width, const unsigned int & height, const unsigned int & depth)
{
  if (!Single::isInit())
    return false;

  unsigned int _height = height?height:1;

  glViewport( 0, 0, (GLint)width, (GLint)_height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho( 0, width,_height,0, -depth, depth );

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  Single::get()->m_height = _height;
  Single::get()->m_width = width;
  Single::get()->m_depth = depth;
  refresh();
  return true;
}


/** @brief refresh
 *	draw objects on screen
 * @return true if successful
 */
template <typename DupObject>
bool Renderer<DupObject>::refresh()
{

  if (!Single::isInit())
    return false;

  if (!isSetup())
    return false;

  if(SelectionRender::get()->getUpdated())
  {
    update( TimeManager::getTurn(), 0 );
  }

  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  std::map<int, renderObj*>::iterator it = Single::get()->m_renderConstant.begin();

  #if 1
  for( ; it != Single::get()->m_renderConstant.end(); it++ )
  {
    GOCFamily_Render *r = (GOCFamily_Render*)it->second->getGOC( "RenderFamily" );
    if( r )
    {
      r->renderAt( TimeManager::getTurn(), 0 );
    }
  }
  #endif

  glPushMatrix();
  float mapSize = (float)OptionsMan::getInt("mapSize");
  glScalef( height()/mapSize, height()/mapSize, 1 );

  typename std::vector<DupObject*>::iterator renderIt = Single::get()->m_renderList.begin();
  for (; renderIt != Single::get()->m_renderList.end(); renderIt++)
  {
    glPushMatrix();
    (*renderIt)->render();
    glPopMatrix();
  }

  glPopMatrix();

  if( Single::get()->m_parent )
  {
    Single::get()->m_parent->swapBuffers();
  }

  SelectionRender::get()->setUpdated(false);

  return true;
}


template <typename DupObject>
void Renderer<DupObject>::setParent( RenderWidget *parent )
{
  if (!Single::isInit())
    return;                      //! @todo throw error
  Single::get()->m_parent = parent;
}


/** @brief destroy
 * destroy the singleton
 * @return true on success
 */
template <typename DupObject>
bool Renderer<DupObject>::destroy()
{
  if(!Single::isInit())
    return false;
  if (!clear())
    return false;

  return Single::destroy();
}


/** @brief create
 * create the singleton and setup the render area
 * @return true on success
 */
template <typename DupObject>
bool Renderer<DupObject>::create()
{
  if (!Single::create())
    return false;

  Single::get()->m_parent = 0;
  Single::get()->m_height = 0;
  Single::get()->m_width  = 0;
  Single::get()->m_depth  = 10;
  Single::get()->m_dupListDirs = 0;
  Single::get()-> m_duplicateList = NULL;

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

  if (get()->m_objects.find(id) == get()->m_objects.end())
    return NULL;

  return get()->m_objects[id];
}*/

/** @brief setup
 * setup the rendering for the render, size the screen according to
 *	the width and height given
 * @return true if successful
 * @todo add more to the render setup
 */
template <typename DupObject>
bool Renderer<DupObject>::setup()
{
  if (!Single::isInit())
  {
    std::cout << "Renderer Error: Trying to set up an uninitialized Renderer\n";
    return false;
  }

  /** @todo fill this in with more setup information */
  if ( Single::get()->m_width && Single::get()->m_height && Single::get()->m_depth )
  {
    resize( Single::get()->m_width, Single::get()->m_height, Single::get()->m_depth );
  }
  else if ( Single::get()->m_width && Single::get()->m_height )
  {
    resize( Single::get()->m_width, Single::get()->m_height );
  }
  else if ( OptionsMan::isInit() )
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

  if (Single::get()->m_dupListDirs)
  {
    Single::get()->m_duplicateList = new DupObject***[rwidth];
    for (unsigned int x = 0; x < width(); x++)
    {
      Single::get()->m_duplicateList[x] = new DupObject**[rheight];
      for (unsigned int y = 0; y < height(); y++)
      {
        Single::get()->m_duplicateList[x][y] = new DupObject*[rdepth];
        for (unsigned int z = 0; z < rdepth; z++)
        {
          Single::get()->m_duplicateList[x][y][z] = new DupObject[Single::get()->m_dupListDirs];
        }
      }
    }
  }
  else if (OptionsMan::exists(renderDirsName) && OptionsMan::optionType(renderDirsName) == OT_INT)
  {
    Single::get()->m_dupListDirs = OptionsMan::getInt(renderDirsName);
    Single::get()->m_duplicateList = new DupObject***[width()];
    for (unsigned int x = 0; x < width(); x++)
    {
      Single::get()->m_duplicateList[x] = new DupObject**[height()];
      for (unsigned int y = 0; y < height(); y++)
      {
        Single::get()->m_duplicateList[x][y] = new DupObject*[depth()];
        for (unsigned int z = 0; z < depth(); z++)
        {
          Single::get()->m_duplicateList[x][y][z] = new DupObject[Single::get()->m_dupListDirs];
        }
      }
    }
  }
  else
  {
    Single::get()->m_duplicateList = new DupObject***[width()];
    for (unsigned int x = 0; x < width(); x++)
    {
      Single::get()->m_duplicateList[x] = new DupObject**[height()];
      for (unsigned int y = 0; y < height(); y++)
      {
        Single::get()->m_duplicateList[x][y] = new DupObject*[depth()];
        for (unsigned int z = 0; z < depth(); z++)
        {
          Single::get()->m_duplicateList[x][y][z] = new DupObject[1];
        }
      }
    }
    Single::get()->m_dupListDirs = 1;
  }

  /// @TODO: Move this to the appropriate spot
  glShadeModel( GL_SMOOTH );
  glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
  glClearDepth( 1.0f );

  glEnable( GL_DEPTH_TEST );
  glDepthFunc( GL_LEQUAL );

  Single::get()->m_isSetup = true;

  glDisable( GL_TEXTURE_2D );
  glEnable( GL_BLEND );
  glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

  refresh();
  return Single::get()->m_isSetup;
}


/** @brief isSetup
 * access if the module has been set up
 * @return true if set up
 */
template <typename DupObject>
bool Renderer<DupObject>::isSetup()
{
  if (!Single::isInit())
    return false;

  return Single::get()->m_isSetup;
}


/** @brief clear
 * clear all references to render objects
 * @return true on success
 */
template <typename DupObject>
bool Renderer<DupObject>::clear()
{
  if (!Single::isInit())
    return false;

  #if 0
  if (Single::get()->m_duplicateList)
  {
    for (unsigned int x = 0; x < width(); x++)
    {
      for (unsigned int y = 0; y < height(); y++)
      {
        for (unsigned int z = 0; z < depth(); z++)
        {
          delete Single::get()->m_duplicateList[x][y][z];
        }
        delete [] Single::get()->m_duplicateList[x][y];
      }
      delete [] Single::get()->m_duplicateList[x];
    }
    delete [] Single::get()->m_duplicateList;
  }
  #endif

  Single::get()->m_duplicateList = NULL;

  std::map<int, renderObj*>::iterator it = Single::get()->m_renderConstant.begin();
  for(; it!=Single::get()->m_renderConstant.end(); it++ )
  {
    delete (it->second);
  }

  Single::get()->m_renderConstant.clear();

  return true;
}


template<typename DupObject>
bool Renderer<DupObject>::registerConstantObj( const unsigned int& id, renderObj* obj )
{
  if (!Single::isInit())
  {
    return false;
  }

  if( Single::get()->m_renderConstant.find( id ) != Single::get()->m_renderConstant.end() )
  {
    return false;
    delete Single::get()->m_renderConstant[id];
  }

  Single::get()->m_renderConstant[id] = obj;

  return true;
}


template<typename DupObject>
bool Renderer<DupObject>::deleteConstantObj( const unsigned int& id )
{
  std::map<int,renderObj*> it = Single::get()->m_renderConstant.find( id );
  if( it != Single::get()->m_renderConstant.end() )
  {
    delete Single::get()->m_renderConstant[id];
    Single::get()->m_renderConstant.erase( it );
    return true;
  } else
  {
    return false;
  }

}


/** @brief updateLocation
 *
 * @todo: document this function
 */
template <typename DupObject>
void Renderer<DupObject>::updateLocation(const unsigned int & x, const unsigned int & y, const unsigned int & z, const unsigned int & dir, const unsigned int & time, DupObject obj)
{
  //std::cout << "updateLocation Called\n";

  if (!Single::isInit())
    return;

  if (!isSetup())
    return;

  if (x > width() || y > height() || z > depth() || dir > Single::get()->m_dupListDirs)
    return;                      //! @todo throw an error

  bool sameFlag = false;

  if (obj.time == time)
  {
    sameFlag = true;
  }

  obj.x = x;
  obj.y = y;

  obj.time = time;
  Single::get()->m_duplicateList[x][y][z][dir] += obj;

  if (!sameFlag)
  {
    Single::get()->m_renderList.push_back(&(Single::get()->m_duplicateList[x][y][z][dir]));
    //std::cout << "Gets to add\n";
  }
}


/**
 * @todo doxyment
 */
template <typename DupObject>
unsigned int Renderer<DupObject>::width()
{
  if (isSetup())
    return Single::get()->m_width;

  return 0;
}


/**
 * @todo doxyment
 */
template <typename DupObject>
unsigned int Renderer<DupObject>::height()
{
  if (isSetup())
    return Single::get()->m_height;

  return 0;
}


/**
 * @todo doxyment
 */
template <typename DupObject>
unsigned int Renderer<DupObject>::depth()
{
  if (isSetup())
    return Single::get()->m_depth;

  return 0;
}


/**
 * @todo doxyment
 */
template <typename DupObject>
bool Renderer<DupObject>::update(const unsigned int & turn, const unsigned int & frame)
{
  Stats globalTotal, globalP0, globalP1, globalP2, globalP3; 
  Stats selectedTotal, selectedP0, selectedP1, selectedP2, selectedP3; 
  int health;

  if (!Single::isInit())
  {
    std::cout << "Update Failed: Renderer is not inititalized or setup\n";
    return false;
  }                              //! @todo fuck off

  typedef std::map<ObjIdType,LookupNode<GameObject*,ObjIdType>* > Bucket;
  Bucket * bucket = ObjectManager::getBucket(turn,frame);

  if (!bucket)
  {
    std::cout << "Bucket Requested at (" << turn <<","<<frame << ") does not exist\n";
    return false;
  }

  Single::get()->m_renderList.clear();
  int time = TimeManager::timeHash();

  bool selectUpdate = SelectionRender::get()->getUpdated();
  float mapSize = (float)OptionsMan::getInt("mapSize");
  float unitSize  = height()/mapSize;

  int x1 = 0;
  int x2 = 0;
  int y1 = 0;
  int y2 = 0;

  if( selectUpdate )
  {

    x1 = SelectionRender::get()->getX1()/unitSize;
    x2 = SelectionRender::get()->getX2()/unitSize;
    if( x2 < x1 )
    {
      int temp;
      temp = x2;
      x2 = x1;
      x1 = temp;
    }

    y1 = SelectionRender::get()->getY1()/unitSize;
    y2 = SelectionRender::get()->getY2()/unitSize;

    if( y2 < y1 )
    {
      int temp;
      temp = y1;
      y1 = y2;
      y2 = temp;
    }
  
    Single::get()->selectedUnitIds.clear();
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
            Single::get()->selectedUnitIds.insert( id );
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


        if( Single::get()->selectedUnitIds.find( it->first ) != Single::get()->selectedUnitIds.end() )
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
              Single::get()->appendToConsole( ((GOCFamily_Talk*)goc)->message() );
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

    }

  }

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

  Single::get()->globalStatColumnPopulate (globalTotal, 0);
  Single::get()->globalStatColumnPopulate (globalP0, 1);
  Single::get()->globalStatColumnPopulate (globalP1, 2);
  Single::get()->globalStatColumnPopulate (globalP2, 3);
  Single::get()->globalStatColumnPopulate (globalP3, 4);

  Single::get()->selectionStatColumnPopulate (selectedTotal, 0);
  Single::get()->selectionStatColumnPopulate (selectedP0, 1);
  Single::get()->selectionStatColumnPopulate (selectedP1, 2);
  Single::get()->selectionStatColumnPopulate (selectedP2, 3);
  Single::get()->selectionStatColumnPopulate (selectedP3, 4);
  
  return true;
}

template<typename DupObject>
void Renderer<DupObject>::printToTable( QTableWidget *w, int c, int r, QString str )
{
  if( w->itemAt( c, r ) )
  {
    w->itemAt( c, r )->setText( str );
  } else {
    w->setItem( c, r, new QTableWidgetItem( str ) );
  }

}

template<typename DupObject>
void Renderer<DupObject>::printIndividuals( int c, int r, QString str )
{
  printToTable( GUI::getIndividualStats(), c, r, str );
}

template<typename DupObject>
void Renderer<DupObject>::printSelectedStats( int r, int c, QString str )
{
  printToTable( GUI::getSelectionStats(), c, r, str );
}

template<typename DupObject>
void Renderer<DupObject>::printGlobalStats( int r, int c, QString str )
{
  printToTable( GUI::getGlobalStats(), c, r, str );
}

template<typename DupObject>
void Renderer<DupObject>::appendToConsole( string str )
{
  GUI::appendConsole( str );
}

template<typename DupObject>
void Renderer<DupObject>::individualStatColumnPopulate (int id, DupObject unit, int column)
{
  Single::get()->printSelectedStats( column, 1, QString::number(id));
  Single::get()->printSelectedStats( column, 2, QString::number(unit.owner));
  Single::get()->printSelectedStats( column, 3, QString::number(unit.objType));
  Single::get()->printSelectedStats( column, 4, QString::number(unit.health));
  Single::get()->printSelectedStats( column, 5, QString::number(unit.gold));
  Single::get()->printSelectedStats( column, 6, QString::number(unit.x));
  Single::get()->printSelectedStats( column, 7, QString::number(unit.y));
  Single::get()->printSelectedStats( column, 8, QString::number(unit.treasures));
}

template<typename DupObject>
void Renderer<DupObject>::selectionStatColumnPopulate (Stats multi, int column)
{
  Single::get()->printSelectedStats( column, 1, QString::number(multi.pirates));
  Single::get()->printSelectedStats( column, 2, QString::number(multi.avgPirateHealth));
  Single::get()->printSelectedStats( column, 3, QString::number(multi.avgPirateGold));
  Single::get()->printSelectedStats( column, 4, QString::number(multi.gold));
  Single::get()->printSelectedStats( column, 5, QString::number(multi.ships));
  Single::get()->printSelectedStats( column, 6, QString::number(multi.avgShipHealth));
  Single::get()->printSelectedStats( column, 7, QString::number(multi.avgShipGold));
  Single::get()->printSelectedStats( column, 8, QString::number(multi.treasures));
  //Single::get()->printSelectedStats( column, 0, QString::number(0));
}

template<typename DupObject>
void Renderer<DupObject>::globalStatColumnPopulate (Stats multi, int column)
{
  Single::get()->printGlobalStats( column, 1, QString::number(multi.pirates));
  Single::get()->printGlobalStats( column, 2, QString::number(multi.avgPirateHealth));
  Single::get()->printGlobalStats( column, 3, QString::number(multi.avgPirateGold));
  Single::get()->printGlobalStats( column, 4, QString::number(multi.gold));
  Single::get()->printGlobalStats( column, 5, QString::number(multi.ships));
  Single::get()->printGlobalStats( column, 6, QString::number(multi.avgShipHealth));
  Single::get()->printGlobalStats( column, 7, QString::number(multi.avgShipGold));
  Single::get()->printGlobalStats( column, 8, QString::number(multi.treasures));
  //Single::get()->printGlobalStats( column, 0, QString::number(0));
}
#endif
