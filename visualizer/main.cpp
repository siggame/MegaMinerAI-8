
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
	typedef Renderer<DupObj> Render;

	QApplication app( argc, argv );

	if (!OptionsMan::create())
	    return 1;

	if (!GUI::create())
	    return 1;

	if (!ResourceMan::create())
	    return 1;

	if (!Mutex::create())
	    return 1;

	if (!Threadler::create())
	    return 1;

	if (!ObjectManager::create())
	    return 1;


	if (!ObjectLoader::create())
	    return 1;

	if (!TimeManager::create())
	    return 1;

	if( !OptionsMan::loadOptionFile( "./options.cfg" ) )
	{
		std::cerr << "Could Not Load options.cfg" << std::endl;
		TimeManager::destroy();
		OptionsMan::destroy();
		ResourceMan::destroy();
		Mutex::destroy();
		Threadler::destroy();
		Render::destroy();
		GUI::destroy();
		ObjectManager::destroy();
		ObjectLoader::destroy();
		return 1;
	}

	// initialize global options
	OptionsMan::addInt("numTurns",1);
	OptionsMan::addBool("sliderDragging", false );
	OptionsMan::addInt( "currentTurn", 0 );
	// done initializing

	TimeManager::setSpeed( 1 );

	GUI::setup();
	Render::setup();

	if ( !ResourceMan::loadResourceFile("./textures.r") )
	{
		std::cerr << "Could Not Load resource.cfg" << std::endl;
		TimeManager::destroy();
		OptionsMan::destroy();
		ResourceMan::destroy();
		Mutex::destroy();
		Threadler::destroy();
		GUI::destroy();
		Render::destroy();
		ObjectManager::destroy();
		ObjectLoader::destroy();
		return 1;
	}

	if( argc > 1 )
	{
	    GUI::loadGamelog( argv[1] );
	}

  TimeManager::timerStart();

	int retval = app.exec();

	Render::destroy();
	TimeManager::destroy();
	GUI::destroy();
	OptionsMan::destroy();
	ResourceMan::destroy();
	Mutex::destroy();
	Threadler::destroy();
	ObjectManager::destroy();
	ObjectLoader::destroy();
	return retval;
}
