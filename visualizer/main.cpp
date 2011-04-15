
#include <iostream>
#include "lib/gui/gui.h"
#include "lib/optionsmanager/optionsman.h"
#include "lib/timemanager/timeManager.h"
#include "lib/mutex/Mutex.h"
#include "lib/threadler/threadler.h"
#include "lib/resourcemanager/resourceman.h"
#include "lib/resourcemanager/texture.h"
#include "lib/objectmanager/objectmanager.h"
#include "piracy/dupObj.h"

int main(int argc, char *argv[])
{
	typedef Renderer<DupObj> Render;
	QApplication app( argc, argv );
	TimeManager::create();
	TimeManager::setSpeed( 1 );

	optionsMan::create();
	GUI::create();
	ResourceMan::create();
	Mutex::create();
	Threadler::create();
	Render::create();
	ObjectManager::create();
	ObjectLoader::create();


	if( !optionsMan::loadOptionFile( "./options.cfg" ) )
	{
		std::cerr << "Could Not Load options.cfg" << std::endl;
		TimeManager::destroy();
		optionsMan::destroy();
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
	optionsMan::addInt("numTurns",1);
	optionsMan::addBool("sliderDragging", false );
	optionsMan::addInt( "currentTurn", 0 );
	// done initializing

	GUI::setup();


	Render::setup();

	if ( !ResourceMan::loadResourceFile("./textures.r") )
	{
		std::cerr << "Could Not Load resource.cfg" << std::endl;
		TimeManager::destroy();
		optionsMan::destroy();
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
		GUI::loadGamelog( argv[1] );


	Render::refresh();

	int retval = app.exec();

	Render::destroy();
	TimeManager::destroy();
	GUI::destroy();
	optionsMan::destroy();
	ResourceMan::destroy();
	Mutex::destroy();
	Threadler::destroy();
	ObjectManager::destroy();
	ObjectLoader::destroy();
	return retval;
}
