#include "frame.h"
#include "viruses.h"
#include "botnet.h"

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
    lr.regex = "Plant";
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

      }
        

    }



  } // BotNet::loadGamelog() 

} // visualizer

Q_EXPORT_PLUGIN2( botnet, visualizer::BotNet );
