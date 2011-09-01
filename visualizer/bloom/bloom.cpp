#include "bloom.h"
#include "plant.h"
#include "frame.h"
#include "animations.h"

namespace visualizer
{

  Bloom::Bloom()
  {
    m_game = 0;
  } // Bloom::Bloom()

  Bloom::~Bloom()
  {
    delete m_game;
  } // Bloom::~Bloom()

  LogRegex Bloom::logFileInfo()
  {
    LogRegex lr;
    lr.regex = "Plant";
    lr.startSize = 500;

    return lr;

  } // Bloom::logFileInfo()
  
  void Bloom::loadGamelog( std::string gamelog )
  {

    cout << "Load Bloom Gamelog" << endl;
    unsigned int frameNum = 0;
    delete m_game;
    m_game = new Game;
    if( !parseFile( *m_game, (char*)gamelog.c_str() ) )
    {
      delete m_game;
      THROW
        (
          GameException, "Cannot Load The Gamelog."
        );

      m_intf.resourceManager->loadResourceFile( "./plugins/bloom/textures.r" );
    }

    for
      (
      std::vector<GameState>::iterator state = m_game->states.begin();
      state != m_game->states.end();
      state++
      )
    {
      Frame turn;
      for
        (
        std::vector<Plant>::iterator i = state->plants.begin();
        i != state->plants.end();
        i++
        )
      {
        plant *p = new plant;
        p->addKeyFrame( new StartAnim( p ) );



        p->addKeyFrame( new DrawAnim( p ) );
        turn.addAnimatable( p );

      }
      // turn.addAnimatable( score and stuff );
      addFrame( turn );
      frameNum++;
      m_intf.timeManager->setNumTurns( frameNum );
      m_intf.timeManager->updateProgress( (float)frameNum/m_game->states.size() );

      if( frameNum <= 1 )
      {
        m_intf.animationEngine->registerFrameContainer( this );
        m_intf.timeManager->play();
      }

    }

  } // Bloom::loadGamelog()

  void Bloom::registerInterfaces( Interfaces intf )
  {
    m_intf = intf;

  } // Bloom::registerInterfaces

} // visualizer

Q_EXPORT_PLUGIN2( bloom, visualizer::Bloom );
