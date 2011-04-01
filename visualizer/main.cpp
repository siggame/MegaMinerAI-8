#include "lib/timeline/avl.h"
#include <iostream>
#include "lib/gui/gui.h"
#include "lib/optionsmanager/optionsman.h"

int main(int argc, char *argv[])
{

  QApplication app( argc, argv );
  GUI::create();
  if( argc > 1 )
    GUI::loadGamelog( argv[1] );

  if( !optionsMan::loadOptionFile( "options.cfg" ) )
  {
    std::cerr << "Could Not Load options.cfg" << std::endl;
  }

	return app.exec();
}
