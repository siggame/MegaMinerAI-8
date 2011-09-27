#include "bloom.h"
#include "plant.h"
#include "frame.h"
#include "animations.h"

namespace visualizer
{
  Bloom::Bloom()
  {
    m_game = 0;
  }

  Bloom::~Bloom()
  {
    delete m_game;
  }

  LogRegex Bloom::logFileInfo()
  {
    LogRegex lr;
    lr.regex = "Plant";
    lr.startSize = 500;

    return lr;
  }

  void Bloom::loadGamelog( std::string gamelog )
  {
    cout << "Load Bloom Gamelog" << endl;

    delete m_game;

    m_game = new Game;

    if( !parseFile( *m_game, (char*)gamelog.c_str() ) )
    {
      delete m_game;
      THROW
        (
        GameException, 
        "Cannot load gamelog: %s", 
        gamelog.c_str()
        );
    }

    resourceManager->loadResourceFile( "./plugins/piracy/textures.r" );

    size_t frameNum = 0;

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
        plant *p = new plant( renderer );

        p->addKeyFrame( new StartAnim );

        p->ownerID = i->ownerID;
        p->x = i->x;
        p->y = i->y;
        p->root = i->root;
        p->leaf = i->leaf;
        p->flower = i->flower;
        p->health = i->health;

        p->addKeyFrame( new DrawPlant( p ) );

        turn.addAnimatable( p );
      }

      addFrame( turn );

      frameNum++;

    }

    timeManager->setNumTurns( frameNum );

    animationEngine->registerFrameContainer( this );

    timeManager->play();

  }

} // visualizer

Q_EXPORT_PLUGIN2( bloom, visualizer::Bloom );
