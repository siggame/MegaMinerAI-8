#include "piracy.h"
#include "common.h"
#include "parser/parser.h"
#include "parser/structures.h"
#include <iostream>

namespace visualizer
{

LogRegex Piracy::logFileInfo()
{
  LogRegex lr;
  lr.regex = "";

  
  return lr;
};

void Piracy::registerInterfaces( Interfaces intf ) 
{
  m_intf = intf;
}

void Piracy::loadGamelog( std::string gamelog )
{
  Game game;
  if( !parseFile( game, gamelog.c_str() ) )
  {
    THROW( Exception, "Cannot Load The Gamelog" );
  }

  GameObject *go = new GameObject( 1 );
#if 0
  PirateMap *pm = new PirateMap();
#endif



  //THROW( Exception, "LOADING PIRACY GAMELOG" );
}

} // visualizer

Q_EXPORT_PLUGIN2( piracy, visualizer::Piracy );
