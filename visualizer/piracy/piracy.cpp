#include "piracy.h"
#include "common.h"
#include <iostream>

LogRegex Piracy::logFileInfo()
{
  LogRegex lr;
  
  return lr;
};

void Piracy::loadGamelog( std::string gamelog )
{
#if 0
  std::cerr << gamelog << std::endl;
  std::cout << "Loading Piracy Gamelog" << std::endl;
  throw "LOADING PIRACY GAMELOG";
#endif

  THROW( Exception, "LOADING PIRACY GAMELOG" );

}

Q_EXPORT_PLUGIN2( piracy, Piracy );
