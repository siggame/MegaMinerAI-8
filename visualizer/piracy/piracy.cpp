#include "piracy.h"
#include "common.h"
#include "parser/parser.h"
#include "parser/structures.h"
#include <iostream>

LogRegex Piracy::logFileInfo()
{
  LogRegex lr;
  lr.regex = "";

  
  return lr;
};

void Piracy::loadGamelog( std::string gamelog )
{
  Game game;
  if( !parseFile( game, gamelog.c_str() ) )
  {
    THROW( Exception, "Cannot Load The Gamelog" );
  }


  //THROW( Exception, "LOADING PIRACY GAMELOG" );

}

Q_EXPORT_PLUGIN2( piracy, Piracy );
