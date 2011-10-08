#include "frame.h"
#include "viruses.h"
#include "botnet.h"
#include "animations.h"

namespace visualizer
{
  BotNet::BotNet()
  {
    m_game = 0;
  } // BotNet::BotNet()

  BotNet::~BotNet()
  {
    delete m_game;
  } // BotNet::~BotNet()

  LogRegex BotNet::logFileInfo()
  {
    LogRegex lr;
    lr.regex = "Virus";
    lr.startSize = 500;

    return lr;
  } // BotNet::logFileInfo()

  void BotNet::loadGamelog( std::string gamelog )
  {
    cout << "Load BotNet Gamelog" << endl;
    
    delete m_game;
    m_game = new Game;

    if( !parseFile( *m_game, gamelog.c_str() ) )
    {
      delete m_game;
      THROW
        (
        GameException,
        "Cannot load gamelog: %s", 
        gamelog.c_str()
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
        std::map<int, Virus>::iterator i = state->viruses.begin();
        i != state->viruses.end();
        i++ 
        )
      {
        virus* v = new virus( renderer );

        v->addKeyFrame( new StartAnim );
        v->id = i->second.id;
        v->owner = i->second.owner;
        v->x = i->second.x;
        v->y = i->second.y;
        v->level = i->second.level;
        v->movesLeft = i->second.movesLeft;
        v->addKeyFrame( new DrawVirus( v ) );

        turn.addAnimatable( v );

      }

      addFrame( turn );
      
      frameNum++;

    }

    timeManager->setNumTurns( frameNum );

    animationEngine->registerFrameContainer( this );

    timeManager->play();

  } // BotNet::loadGamelog() 

} // visualizer

Q_EXPORT_PLUGIN2( botnet, visualizer::BotNet );
