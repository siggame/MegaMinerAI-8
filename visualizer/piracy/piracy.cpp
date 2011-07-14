#include "piracy.h"
#include "common.h"
#include "parser/parser.h"
#include "parser/structures.h"
#include "renderer/renderer.h"
#include "resourcemanager/texture.h"
#include "selectionrender/selectionrender.h"
#include "scoreboard.h"

#include <iostream>

typedef int idtype;

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

#if 0
  go = new GameObject( 2 );
  go->setGOC( SelectionRender );
  SelectionRender->setOwner( go );

  go = new GameObject( 3 );
  Scoreboard *sb = new Scoreboard();
  ResTexture res;
  res.load( "./textures/font1.png" );
  sb->loadFont( res.getTexture(), "./textures/font1.dat" );
  sb->parseScores( game );

  sb->setOwner( go );
  go->setGOC( sb );

  Renderer->registerConstantObj( 3, go );

  unsigned int numTurns = game.states.size();
  unsigned int numFrames = OptionsMan->getInt( "numFrames" );

  ObjectManager->setSize( numTurns, numFrames );

  TimeManager->setTurn( 0 );
  TimeManager->setNumTurns( numTurns );

  std::map<idtype, LookupSet<GameObject*, idtype> > looksets;
  unsigned int id;
  for( unsigned int turn = 0; turn < game.states.size(); turn++ )
  {
  }

#endif
  //THROW( Exception, "LOADING PIRACY GAMELOG" );
}

} // visualizer

Q_EXPORT_PLUGIN2( piracy, visualizer::Piracy );

