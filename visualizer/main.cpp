#include "lib/timeline/avl.h"
#include <iostream>
#include "lib/gui/gui.h"
#include "lib/optionsmanager/optionsman.h"
#include "lib/timemanager/timeManager.h"

int main(int argc, char *argv[])
{

  QApplication app( argc, argv );
  TimeManager::create();
  GUI::create();
  if( argc > 1 )
    GUI::loadGamelog( argv[1] );

  if( !optionsMan::loadOptionFile( "./options.cfg" ) )
  {
    std::cerr << "Could Not Load options.cfg" << std::endl;
  }

	return app.exec();
}
