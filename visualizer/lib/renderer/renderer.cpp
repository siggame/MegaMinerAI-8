#include "renderer.h"
#include "../timemanager/timeManager.h"
#include "../../piracy/piratemap.h"
#include "../gui/gui.h"

/** @brief numObjects
  * the number of objects registered
  * @return the number of objects registered
  */
unsigned int Renderer::numObjects()
{
	if (!isInit())
		return 0;
	return get()->m_objects.size();
}

/** @brief resize
  * resize and refresh the projection  and modelview matricies
  * @param width the x size of the render area.
  * @param height the y size of the render area.
  * @param depth the z depth of the render area. default 10
  * @return true if successful resize
  */
bool Renderer::resize(const unsigned int & width, const unsigned int & height, const unsigned int & depth)
{
	if (!isInit())
		return false;

	unsigned int _height = height?height:1;

	glViewport( 0, 0, (GLint)width, (GLint)_height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho( 0, width, _height, 0, 0, depth );


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	get()->m_height = _height;
	get()->m_width = width;
	get()->m_depth = depth;
  refresh();
	return true;
}

#include <iostream>
using namespace std;

/** @brief refresh
  *	draw objects on screen
  * @return true if successful
  */
bool Renderer::refresh()
{
	if (!isInit())
		return false;
	if (!isSetup())
		return false;

  GUI::update();

  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	/** @todo change this to the proper accessors */
	//get time (turn, frame)
	unsigned int turn = TimeManager::getTurn();
	unsigned int frame = TimeManager::getFrame();

  //float depth = 0;
	std::map<unsigned int, renderObj*>::iterator it = get()->m_objects.begin();
	for (; it != get()->m_objects.end(); it++)
	{
		/** @todo fill this in */

    glPushMatrix();
    glScalef( 20, 20, 1 );

    GOCFamily_Render *r = (GOCFamily_Render*)it->second->getGOC( "RenderFamily" );
    if( r )
    {
      r->renderAt(turn,frame);
    }

    glPopMatrix();
	}
  if( get()->m_parent )
  {
    get()->m_parent->swapBuffers();
  }

 // static int p = 0;

	return true;
}

void Renderer::setParent( RenderWidget *parent )
{
  get()->m_parent = parent;
}

/** @brief destroy
  * destroy the singleton
  * @return true on success
  */
bool Renderer::destroy()
{
	if(!isInit())
		return false;
	if (!clear())
		return false;

	return Singleton<Renderer>::destroy();
}

/** @brief create
  * create the singleton and setup the render area
  * @return true on success
  */
bool Renderer::create()
{
	if (!Singleton<Renderer>::create())
		return false;

	get()->m_parent = 0;
	get()->m_height = 0;
	get()->m_width  = 0;
	get()->m_depth  = 0;
	get()->m_dupListDirs = 0;
	get()-> m_duplicateList = NULL;

	return true;
}

/** @brief getRenderObject
  * get the render object associated with the id
  * @param id the GO ID of the render object
  * @return a pointer to the render object
  * @todo figure out if we want multiple render objects to a single game object
  */
renderObj* Renderer::getRenderObject(const unsigned int id)
{
	if (!isInit())
		return NULL;

	if (get()->m_objects.find(id) == get()->m_objects.end())
		return NULL;

	return get()->m_objects[id];
}

/** @brief setup
  * setup the rendering for the render, size the screen according to
  *	the width and height given
  * @return true if successful
  * @todo add more to the render setup
  */
bool Renderer::setup()
{
	if (!isInit())
		return false;

	/** @todo fill this in with more setup information */
	if ( get()->m_width && get()->m_height && get()->m_depth )
	{
		resize( get()->m_width, get()->m_height, get()->m_depth );
	}
	else if ( get()->m_width && get()->m_height )
	{
		resize( get()->m_width, get()->m_height );
	}
	else if ( optionsMan::isInit() )
	{
		if ( optionsMan::exists(renderHeightName) && optionsMan::optionType(renderDepthName) == OT_INT &&
				  optionsMan::exists(renderWidthName) && optionsMan::optionType(renderWidthName) == OT_INT )
		{
			if ( optionsMan::exists(renderDepthName) && optionsMan::optionType(renderDepthName) == OT_INT)
			{
				resize( optionsMan::getInt(renderWidthName),
						optionsMan::getInt(renderHeightName),
						optionsMan::getInt(renderDepthName) );
			}
			else
			{
				resize( optionsMan::getInt(renderWidthName),
						optionsMan::getInt(renderHeightName) );
			}
		}
	}

	if (get()->m_duplicateList)
	{
		for (unsigned int x = 0; x < width(); x++)
		{
			for (unsigned int y = 0; y < height(); y++)
			{
				for (unsigned int z = 0; z < depth(); z++)
				{
					delete [] get()->m_duplicateList[x][y][z];
				}
				delete [] get()->m_duplicateList[x][y];
			}
			delete [] get()->m_duplicateList[x];
		}
		delete [] get()->m_duplicateList;
	}

	if (get()->m_dupListDirs)
	{
		get()->m_duplicateList = new DupObj***[width()];
		for (unsigned int x = 0; x < width(); x++)
		{
			get()->m_duplicateList[x] = new DupObj**[height()];
			for (unsigned int y = 0; y < height(); y++)
			{
				get()->m_duplicateList[x][y] = new DupObj*[depth()];
				for (unsigned int z = 0; z < depth(); z++)
				{
					get()->m_duplicateList[x][y][z] = new DupObj[get()->m_dupListDirs];
				}
			}
		}
	}
	else if (optionsMan::exists(renderDirsName) && optionsMan::optionType(renderDirsName) == OT_INT)
	{
		get()->m_dupListDirs = optionsMan::getInt(renderDirsName);
		get()->m_duplicateList = new DupObj***[width()];
		for (unsigned int x = 0; x < width(); x++)
		{
			get()->m_duplicateList[x] = new DupObj**[height()];
			for (unsigned int y = 0; y < height(); y++)
			{
				get()->m_duplicateList[x][y] = new DupObj*[depth()];
				for (unsigned int z = 0; z < depth(); z++)
				{
					get()->m_duplicateList[x][y][z] = new DupObj[get()->m_dupListDirs];
				}
			}
		}
	}
	else
	{
		get()->m_duplicateList = new DupObj***[width()];
		for (unsigned int x = 0; x < width(); x++)
		{
			get()->m_duplicateList[x] = new DupObj**[height()];
			for (unsigned int y = 0; y < height(); y++)
			{
				get()->m_duplicateList[x][y] = new DupObj*[depth()];
				for (unsigned int z = 0; z < depth(); z++)
				{
					get()->m_duplicateList[x][y][z] = new DupObj[1];
				}
			}
		}
		get()->m_dupListDirs = 1;
	}

  /// @TODO: Move this to the appropriate spot
  glShadeModel( GL_SMOOTH );
  glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
  glClearDepth( 1.0f );

  glEnable( GL_DEPTH_TEST );
  glDepthFunc( GL_LEQUAL );
  get()->m_isSetup = true;


  refresh();

  glDisable( GL_TEXTURE_2D );
  glEnable( GL_BLEND );
  glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );


	return get()->m_isSetup;
}

/** @brief del
  * delete a reference to a render object
  * @param id the id associated with the render object
  * @return true on success
  */
bool Renderer::del(const unsigned int & id)
{
	if (!isInit())
		return false;

	if (get()->m_objects.find(id) == get()->m_objects.end())
		return false;

	get()->m_objects.erase(id);

	return true;
}

/** @brief reg
  * register a reference to a render object
  * @param id the id of the render object to add
  * @param obj the reference to add
  * @return true on success
  */
bool Renderer::reg(const unsigned int & id, renderObj * obj)
{
	if (!isInit())
		return false;

	if (get()->m_objects.find(id) != get()->m_objects.end())
		return false;

	get()->m_objects[id] = obj;
	return true;
}

/** @brief depth
  *	accessthe depth of the render volume
  * @return depth
  */
unsigned int Renderer::depth()
{
	if (!isInit())
		return 0;

	return get()->m_depth;
}

/** @brief isSetup
  * access if the module has been set up
  * @return true if set up
  */
bool Renderer::isSetup()
{
	if (!isInit())
		return false;

	return get()->m_isSetup;
}

/** @brief clear
  * clear all references to render objects
  * @return true on success
  */
bool Renderer::clear()
{
	if (!isInit())
		return false;

	get()->m_objects.clear();

	return true;
}

/** @brief updateLocation
  *
  * @todo: document this function
  */
void Renderer::updateLocation(const unsigned int & x, const unsigned int & y, const unsigned int & z, const unsigned int & dir, const unsigned int & time, DupObj obj)
{
	if (!isInit())
		return;

	if (!isSetup())
		return;

	if (x > width() || y > height() || z > depth() || dir > get()->m_dupListDirs)
		return; //! @todo throw an error


	obj.time = time;
	get()->m_duplicateList[x][y][z][dir] +=  obj;

}


