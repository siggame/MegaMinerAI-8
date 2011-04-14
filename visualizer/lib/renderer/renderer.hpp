#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "renderer.h"

/** @brief numObjects
  * the number of objects registered
  * @return the number of objects registered
  *//*
unsigned int Renderer::numObjects()
{
	if (!isInit())
		return 0;
	return get()->m_objects.size();
}*/

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
	glOrtho( 0, width, _height, 0, 0, depth );


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

  //GUI::update();

  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	/** @todo change this to the proper accessors */
	//get time (turn, frame)
	unsigned int turn = TimeManager::getTurn();
	unsigned int frame = TimeManager::getFrame();

  //float depth = 0;
	/*std::map<unsigned int, renderObj*>::iterator it = Single::get()->m_objects.begin();
	for (; it != Single::get()->m_objects.end(); it++)
	{
		//! @todo fill this in

    glPushMatrix();
    glScalef( 20, 20, 1 );

    GOCFamily_Render *r = (GOCFamily_Render*)it->second->getGOC( "RenderFamily" );
    if( r )
    {
      //r->renderAt(turn,frame);
    }

    glPopMatrix();
	}
  if( Single::get()->m_parent )
  {
    Single::get()->m_parent->swapBuffers();
  }

 // static int p = 0;
 */

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
	Single::get()->m_depth  = 0;
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
		return false;

	/** @todo fill this in with more setup information */
	if ( Single::get()->m_width && Single::get()->m_height && Single::get()->m_depth )
	{
		resize( Single::get()->m_width, Single::get()->m_height, Single::get()->m_depth );
	}
	else if ( Single::get()->m_width && Single::get()->m_height )
	{
		resize( Single::get()->m_width, Single::get()->m_height );
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

	clear();

	if (Single::get()->m_dupListDirs)
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
					Single::get()->m_duplicateList[x][y][z] = new DupObject[Single::get()->m_dupListDirs];
				}
			}
		}
	}
	else if (optionsMan::exists(renderDirsName) && optionsMan::optionType(renderDirsName) == OT_INT)
	{
		Single::get()->m_dupListDirs = optionsMan::getInt(renderDirsName);
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


  refresh();

  glDisable( GL_TEXTURE_2D );
  glEnable( GL_BLEND );
  glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );


	return Single::get()->m_isSetup;
}

/** @brief del
  * delete a reference to a render object
  * @param id the id associated with the render object
  * @return true on success
  *//*
bool Renderer::del(const unsigned int & id)
{
	if (!isInit())
		return false;

	if (get()->m_objects.find(id) == get()->m_objects.end())
		return false;

	get()->m_objects.erase(id);

	return true;
}*/

/** @brief reg
  * register a reference to a render object
  * @param id the id of the render object to add
  * @param obj the reference to add
  * @return true on success
  *//*
bool Renderer::reg(const unsigned int & id, renderObj * obj)
{
	if (!isInit())
		return false;

	if (get()->m_objects.find(id) != get()->m_objects.end())
		return false;

	get()->m_objects[id] = obj;
	return true;
}*/


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

	if (Single::get()->m_duplicateList)
	{
		for (unsigned int x = 0; x < width(); x++)
		{
			for (unsigned int y = 0; y < height(); y++)
			{
				for (unsigned int z = 0; z < depth(); z++)
				{
					delete [] Single::get()->m_duplicateList[x][y][z];
				}
				delete [] Single::get()->m_duplicateList[x][y];
			}
			delete [] Single::get()->m_duplicateList[x];
		}
		delete [] Single::get()->m_duplicateList;
	}

	Single::get()->m_duplicateList = NULL;

	return true;
}

/** @brief updateLocation
  *
  * @todo: document this function
  */
template <typename DupObject>
void Renderer<DupObject>::updateLocation(const unsigned int & x, const unsigned int & y, const unsigned int & z, const unsigned int & dir, const unsigned int & time, DupObject obj)
{
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

	obj.time = time;
	Single::get()->m_duplicateList[x][y][z][dir] +=  obj;

	if (!sameFlag)
		Single::get()->m_renderList.push_back(&(Single::get()->m_duplicateList[x][y][z][dir]));

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
#endif
