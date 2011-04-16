#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "renderer.h"
#include "../selectionrender/selectionrender.h"


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
	glOrtho( 0, width, _height, 0, -depth, depth );


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
  }



  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  unsigned int turn = TimeManager::getTurn();
  unsigned int frame = TimeManager::getFrame();


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
  //glScalef( 24.0f, 24.0f, 1.0f );
#if 0
  glDisable(GL_BLEND);
  glColor4f(1.0f,0.0f,1.0f,1.0f);
   glTranslatef(3,3,0);
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
      (*renderIt)->render();\
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

  unsigned int rwidth = width();
  unsigned int rheight = height();
  unsigned int rdepth = depth();

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


  glDisable( GL_TEXTURE_2D );
  glEnable( GL_BLEND );
  glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

  refresh();
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
void Renderer<DupObject>::update(const unsigned int & turn, const unsigned int & frame)
{
    //std::cout << "update?\n";
    if (!Single::isInit())
	return; //! @todo fuck off

    typedef std::map<ObjIdType,LookupNode<GameObject*,ObjIdType>* > Bucket;
    Bucket * bucket = ObjectManager::getBucket(turn,frame);

    if (!bucket)
    {
	//std::cout << "CANT FIND YOUR FUCKING BUCKET\n";
	return; //! @todo toss computer against wall
    }
    else
    {
	//std::cout << "Fucket Size: " << bucket->size() << '\n';
    }

    Single::get()->m_renderList.clear();
    int time = TimeManager::timeHash();

    Bucket::iterator it = bucket->begin();
    for (;it != bucket->end(); it++)
    {
	if (it->second)
	{
	   DupObject temp;
	   setDupObj(it->second->data,temp);	  
	   GOComponent * goc = it->second->data->getGOC("LocationFamily");
	   if (goc)
	   {
	       GOCFamily_Location * loc = (GOCFamily_Location *)(goc);
	       updateLocation(loc->x(),loc->y(),loc->z(),loc->dir(),time,temp);
	   }
	   else
	   {
	       std::cout << "no location for obj type: " << temp.objType << '\n';
	   }

	}

    }

}

#endif

