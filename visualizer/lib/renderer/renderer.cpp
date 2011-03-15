#include "renderer.h"

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

  glClear( GL_COLOR_BUFFER_BIT );

	/** @todo change this to the proper accessors */
	//get time (turn, frame)
	unsigned int turn = 0; // = timeManager::turn();
	unsigned int frame = 0; // = timeManager::frame();

	std::map<unsigned int, renderObj*>::iterator it = get()->m_objects.begin();
	for (it; it != get()->m_objects.end(); it++)
	{
		/** @todo fill this in */
		it->second->renderAt(turn,frame);
	}
	return true;
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
	return setup();
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

  /// @TODO: Move this to the appropriate spot
  glShadeModel( GL_SMOOTH );
  glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
  glClearDepth( 1.0f );

  glEnable( GL_DEPTH_TEST );
  glDepthFunc( GL_LEQUAL );


  glEnable( GL_TEXTURE_2D );
  get()->m_isSetup = true;


  refresh();
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


