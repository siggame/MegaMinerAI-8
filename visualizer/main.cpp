#include "lib/timeline/avl.h"
#include <iostream>
#include "lib/gui/gui.h"

int main(int argc, char *argv[])
{

  QApplication app( argc, argv );
  GUI::create();

	return app.exec();
}
