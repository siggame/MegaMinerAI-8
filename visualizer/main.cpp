
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
  int i = 0;
	typedef Renderer<DupObj> Render;
	QApplication app( argc, argv );

	optionsMan::create();
  cout << "Got to: " << i++ << endl;
	GUI::create();
  cout << "Got to: " << i++ << endl;
	ResourceMan::create();
  cout << "Got to: " << i++ << endl;
	Mutex::create();
  cout << "Got to: " << i++ << endl;
	Threadler::create();
  cout << "Got to: " << i++ << endl;
	ObjectManager::create();
  cout << "Got to: " << i++ << endl;
	ObjectLoader::create();
  cout << "Got to: " << i++ << endl;

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


  cout << "Got to: " << i++ << endl;

	// initialize global options
	optionsMan::addInt("numTurns",1);
	optionsMan::addBool("sliderDragging", false );
	optionsMan::addInt( "currentTurn", 0 );
	// done initializing

	TimeManager::create();
  cout << "Got to: " << i++ << endl;
	TimeManager::setSpeed( 1 );
  cout << "Got to: " << i++ << endl;

  cout << "Got to: " << i++ << endl;
	GUI::setup();
  cout << "Got to: " << i++ << endl;
	Render::setup();
  cout << "Got to: " << i++ << endl;



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


  cout << "Got to: " << i++ << endl;


	if( argc > 1 )
		GUI::loadGamelog( argv[1] );

  cout << "Got to: " << i++ << endl;

	Render::refresh();

  cout << "Got to: " << i++ << endl;
	int retval = app.exec();

  cout << "Got to: " << i++ << endl;
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
