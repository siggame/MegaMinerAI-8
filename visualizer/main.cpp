#include <iostream>
#include "lib/gui/gui.h"
#include "lib/optionsmanager/optionsman.h"
#include "lib/timemanager/timeManager.h"
#include "lib/mutex/Mutex.h"
#include "lib/threadler/threadler.h"
#include "lib/resourcemanager/resourceman.h"
#include "lib/resourcemanager/texture.h"
#include "lib/objectmanager/objectmanager.h"
#include "lib/renderer/renderer.h"
#include "lib/games/games.h"
#include "lib/resourcemanager/textureloader.h"
//#include "piracy/dupObj.h"

using namespace visualizer;

int main(int argc, char *argv[])
{
  ///////////////////////////////////////////////////////////////////
  // Must initialize things based on their dependency graphs
  ///////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////
  // Mutex Depends on Nothing  
  ///////////////////////////////////////////////////////////////////
  Mutex->setup();

  ///////////////////////////////////////////////////////////////////
  // Options Manager Depends On Mutex
  ///////////////////////////////////////////////////////////////////
  OptionsMan->setup();

	if( !OptionsMan->loadOptionFile( "./options.cfg" ) )
	{
		std::cerr << "Could Not Load options.cfg" << std::endl;
		return 1;
	}

	// initialize global options
	OptionsMan->addInt("numTurns",1);
	OptionsMan->addBool("sliderDragging", false );
	OptionsMan->addInt( "currentTurn", 0 );

  ///////////////////////////////////////////////////////////////////
  // Time Manager Depends On Options Manager
  ///////////////////////////////////////////////////////////////////

  TimeManager->setup();

	TimeManager->setSpeed( 1 );

  ///////////////////////////////////////////////////////////////////
  // ObjectManager depends on OptionsManager 
  ///////////////////////////////////////////////////////////////////
  ObjectManager->setup();

  ///////////////////////////////////////////////////////////////////
  // GUI Depends On This Runing, but it doens't depend on anything.
  ///////////////////////////////////////////////////////////////////
	QApplication app( argc, argv );

  ///////////////////////////////////////////////////////////////////
  // SelectionRender depends on OptionsManager 
  ///////////////////////////////////////////////////////////////////
  SelectionRender->setup();

  ///////////////////////////////////////////////////////////////////
  // GUI Depends On Options Manager, Time Manager, Objectmanager,
  // SelectionRender, and QApplication running already.
  // GUI also depends on the renderer, but starts it automagically.
  ///////////////////////////////////////////////////////////////////
	GUI->setup();

  ///////////////////////////////////////////////////////////////////
  // Resource Manager depends on _______________________
  ///////////////////////////////////////////////////////////////////
  ResourceMan->setup();

  ///////////////////////////////////////////////////////////////////
  // Initialize Texture Loader
  ///////////////////////////////////////////////////////////////////
  TextureLoader->setup();

  ///////////////////////////////////////////////////////////////////
  // Initialize Animation Engine
  ///////////////////////////////////////////////////////////////////
  AnimationEngine->setup();

  ///////////////////////////////////////////////////////////////////
  // Initalize the Games
  // This MUST be initialized last, but before loading a gamelog
  // This assigns all the pointers to the interfaces and so all
  // the the interfaces must be set up already.
  ///////////////////////////////////////////////////////////////////
  Games->setup();


	if ( !ResourceMan->loadResourceFile("./textures.r") )
	{
		std::cerr << "Could Not Load resource.cfg" << std::endl;
		return 1;
	}

	if( argc > 1 )
	{
	    GUI->loadGamelog( argv[1] );
	}

  TimeManager->timerStart();

	int retval = app.exec();

  GUI->destroy();
	Renderer->destroy();
  ObjectManager->destroy();
  TimeManager->destroy();
	OptionsMan->destroy();
#if 0
	ResourceMan::destroy();
	Mutex::destroy();
	Threadler::destroy();
	ObjectManager::destroy();
	ObjectLoader::destroy();
#endif
	return retval;
}

