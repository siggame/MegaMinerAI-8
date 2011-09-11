#include "bloom.h"
#include "animations.h"
#include "plant.h"
#include "frame.h"

namespace visualizer
{
  Bloom::Bloom() // Constructor
  {
    m_game = 0;  // Don't setup the game yet.
  }

  Bloom::~Bloom() // Deconstructor
  {
    delete m_game; // Cleanup once we're done
  }

  LogRegex Bloom::logFileInfo() 
      // Function tells the visualizer core what gamelogs we can handle
  {
    LogRegex lr; // Structure which holds regex to determine gamelog 
    // ownership
    lr.regex = "Plant"; // We'll just assume this is a bloom gamelog
    lr.startSize = 500; // How many characters to read before giving up.

    return lr;
  }

  void Bloom::loadGamelog( std::string gamelog )
  {
    cout << "Load Bloom Gamelog" << endl;
    delete m_game; 
    m_game = new Game;

    if( !parseFile( *m_game, (char*)gamelog.c_str() ) ) // Not safe
    {
      delete m_game;
         THROW
        (
          GameException, "Cannot Load The Gamelog."
        );
    }

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

        p->addKeyFrame( new StartAnim() );

        p->x = i->x;
        p->y = i->y;
        p->root = i->root;
        p->flower = i->flower;
        p->leaf = i->leaf;
        p->health = i->health;
        p->ownerID = i->ownerID;

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
}

Q_EXPORT_PLUGIN2( bloom, visualizer::Bloom );
