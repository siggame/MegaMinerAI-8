#include "piracy.h"
#include "common.h"
#include "renderer/renderer.h"
#include "resourcemanager/texture.h"
#include "selectionrender/selectionrender.h"
#include "scoreboard.h"

#include "stacks.h"

#include <iostream>
#include <time.h>

typedef int idtype;

namespace visualizer
{

  LogRegex Piracy::logFileInfo()
  {
    LogRegex lr;
    lr.regex = "\(\"ident\"";
    lr.startSize = 9;
    
    return lr;
  } /* Piracy::logFileInfo() */

  void Piracy::registerInterfaces( Interfaces intf ) 
  {
    m_intf = intf;
  } /* Piracy::registerInterfaces() */

  void Piracy::loadGamelog( std::string gamelog )
  {
    m_game = new Game;
    if( !parseFile( *m_game, gamelog.c_str() ) )
    {
      delete m_game;
      THROW( GameException, "Cannot Load The Gamelog" );
    }

    start();

#if 0
    GameObject *go = new GameObject( 1 );
#if 0
    PirateMap *pm = new PirateMap();
#endif

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
#endif

    Timeline t;
    Turn b;

#if 0
    for
      (
      std::vector<GameState>::iterator i = game.states.begin();
      i != game.states.end(); 
      i++ 
      )
    {

    }
#endif

  } /* Piracy::loadGamelog() */

  void Piracy::run()
  {
    QTime time;
    time.start();

    for
      (
      std::vector<GameState>::iterator i = m_game->states.begin();
      i != m_game->states.end();
      i++
      )
    {
      for
        (
        std::map<int,Pirate>::iterator j = i->pirates.begin();
        j != i->pirates.end();
        j++
        )
      {

      }

      for
        (
        std::map<int,Ship>::iterator j = i->ships.begin();
        j != i->ships.end();
        j++ 
        )
      {

      }
    }

    delete m_game;
    THROW
      (
      Exception,
      "Time Elapsed: %i", 
      time.elapsed()
      );

  } /* Piracy::run() */

} // visualizer

Q_EXPORT_PLUGIN2( piracy, visualizer::Piracy );

