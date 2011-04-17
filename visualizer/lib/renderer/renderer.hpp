#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "renderer.h"
#include "../selectionrender/selectionrender.h"
#include "../goc_owner.h"
#include <sstream>
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
    Single::get()->selectedUnitIds.clear();
    update( TimeManager::getTurn(), TimeManager::getFrame() );
  }



  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  //unsigned int turn = TimeManager::getTurn();
  //unsigned int frame = TimeManager::getFrame();


  std::map<int, renderObj*>::iterator it = Single::get()->m_renderConstant.begin();

#if 1
  for( ; it != Single::get()->m_renderConstant.end(); it++ )
  {
    GOCFamily_Render *r = (GOCFamily_Render*)it->second->getGOC( "RenderFamily" );
    if( r )
    {
      r->renderAt( 0, 0 );
    }
  }
#endif


  glPushMatrix();
  //glTranslatef(0.0f,24.0f,0.0f);
  float mapSize = (float)OptionsMan::getInt("mapSize");
  glScalef( height()/mapSize, height()/mapSize, 1 );
#if 0
  glDisable(GL_BLEND);
  glColor4f(1.0f,0.0f,1.0f,1.0f);
   //glTranslatef(3,3,0);
  glBegin(GL_QUADS);

  glVertex3f(0,0,-1);
  glVertex3f(0,1,-1);
  glVertex3f(1,1,-1);
  glVertex3f(1,0,-1);

  glEnd();
  glEnable(GL_BLEND);

#else

  typename std::vector<DupObject*>::iterator renderIt = Single::get()->m_renderList.begin();
  for (; renderIt != Single::get()->m_renderList.end(); renderIt++)
  {
      glPushMatrix();
      (*renderIt)->render();
      glPopMatrix();
  }

#endif

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
	return; //! @todo throw error
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
		return; //! @todo throw an error

	bool sameFlag = false;

	if (obj.time == time)
	{
		sameFlag = true;
	}

	obj.x = x;
	obj.y = y;

	obj.time = time;
	Single::get()->m_duplicateList[x][y][z][dir] +=  obj;

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
  Stats global, p0, p1, p2, p3, selected;
  int health;



    if (!Single::isInit())
    {
	std::cout << "Update Failed: Renderer is not inititalized or setup\n";
	return false;
    }//! @todo fuck off

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
      
      int temp;
      x1 = SelectionRender::get()->getX1()/unitSize;
      x2 = SelectionRender::get()->getX2()/unitSize;
      if( x2 < x1 )
      {
        temp = x2;
        x2 = x1;
        x1 = temp;
      }

      y1 = SelectionRender::get()->getY1()/unitSize;
      y2 = SelectionRender::get()->getY2()/unitSize;


      if( y2 < y1 )
      {
        temp = y1;
        y1 = y2;
        y2 = temp;
      }


      GUI::clearConsole();
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

             stringstream ss;
#endif
           }
         } else 
         if( Single::get()->selectedUnitIds.find( it->first ) != Single::get()->selectedUnitIds.end() )
         {
           temp.selected = true;
           
           goc = it->second->data->getGOC( "HealthFamily" );
           if( goc )
           {
             health = ((GOCFamily_Health*)goc)->currentHealth();

           }

           goc = it->second->data->getGOC( "ObjectType" );
           if( goc )
           {
             Stats temp;
             switch( ((ObjectType*)goc)->type() )
             {
               case POT_PIRATE:
                 temp.avgPirateHealth = health;

                 temp.pirates = 1;
                 goc = it->second->data->getGOC( "Gold" );
                 temp.gold = ((Gold*)goc)->gold();
                 break;
               case POT_SHIP:
                 temp.avgShipHealth = health;
                 temp.ships = 1;
                 goc = it->second->data->getGOC( "Gold" );
                 temp.gold = ((Gold*)goc)->gold();
                 break;
               case POT_TREAS:
                 temp.treasures = 1;
                 goc = it->second->data->getGOC( "Gold" );
                 temp.gold = ((Gold*)goc)->gold();
                 break;
               default:
                 break;
             }

             switch( owner )
             {
               case 0:
                 p0 += temp;
                 break;
               case 1:
                 p1 += temp;
                 break;
               case 2:
                 p2 += temp;
                 break;
               case 3:
                 p3 += temp;
                 break;
             }

           }

           selected += p0;
           selected += p1;
           selected += p2;
           selected += p3;

         } else {
           temp.selected = false;
         }

         updateLocation(loc->x(),loc->y(),loc->z(),loc->dir(),time,temp);

	   }
	   else
	   {
	       std::cout << "no location for obj type: " << temp.objType << '\n';
	   }

	}

    }

    Single::get()->multipleUnitStatColumnPopulate (p0, 2);

    return true;

}

template<typename DupObject>
void Renderer<DupObject>::multipleUnitStatColumnPopulate (Stats multi, int column)
{
  (GUI::getMultipleStats()->setCellWidget( column, 1, new QLabel( QString::number(multi.gold))));
  //(GUI::getMultipleStats()->itemAt(column, 2))->setText(QString::number(multi.pirates));
}

#endif

