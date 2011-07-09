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
#include "piracy/dupObj.h"

int main(int argc, char *argv[])
{
  ///////////////////////////////////////////////////////////////////
  // Must initialize things based on their dependency graphs
  ///////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////
  // Options Manager Depends On Absolutely Nothing.  INIT FIRST
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
  // GUI Depends On This Runing, but it doens't depend on anything.
  ///////////////////////////////////////////////////////////////////
	QApplication app( argc, argv );

  ///////////////////////////////////////////////////////////////////
  // GUI Depends On Options Manager, Time Manager and QApplication
  // running already
  // GUI also depends on the renderer, but starts it  automagically.
  ///////////////////////////////////////////////////////////////////
	GUI->setup();

	if ( !ResourceMan::loadResourceFile("./textures.r") )
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
