#include "lib/timeline/avl.h"
#include <iostream>
#include "lib/gui/gui.h"
#include "lib/optionsmanager/optionsman.h"
#include "lib/timemanager/timeManager.h"
#include "lib/mutex/Mutex.h"
#include "lib/threadler/threadler.h"
#include "lib/resourcemanager/resourceman.h"
#include "lib/resourcemanager/texture.h"

int main(int argc, char *argv[])
{

	QApplication app( argc, argv );
	TimeManager::create();
	TimeManager::setSpeed( 1 );

	optionsMan::create();
	ResourceMan::create();
	Mutex::create();
	Threadler::create();




	if( !optionsMan::loadOptionFile( "./options.cfg" ) )
	{
		std::cerr << "Could Not Load options.cfg" << std::endl;
		TimeManager::destroy();
		optionsMan::destroy();
		ResourceMan::destroy();
		Mutex::destroy();
		Threadler::destroy();
		return 1;
	}

	if ( !ResourceMan::loadResourceFile("./textures.r") )
	{
		std::cerr << "Could Not Load resource.cfg" << std::endl;
		TimeManager::destroy();
		optionsMan::destroy();
		ResourceMan::destroy();
		Mutex::destroy();
		Threadler::destroy();
		return 1;
	}

	// initialize global options
	optionsMan::addInt("numTurns",1);
	optionsMan::addBool( "sliderDragging", false );
	optionsMan::addInt( "currentTurn", 0 );
	// done initializing


	GUI::create();

	if( argc > 1 )
		GUI::loadGamelog( argv[1] );

	Renderer::refresh();

	int retval = app.exec();

	TimeManager::destroy();
	GUI::destroy();
	optionsMan::destroy();
	ResourceMan::destroy();
	Mutex::destroy();
	Threadler::destroy();

	return retval;
}
