#include "bloom.h"

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
    delete m_game;
    m_game = new Game;
    if( !parseFile( *m_game, (char*)gamelog.c_str() ) )
    {
      delete m_game;
      THROW
        (
          GameException, "Cannot Load The Gamelog."
        );
    }

  } // Bloom::loadGamelog()

  void Bloom::registerInterfaces( Interfaces intf )
  {
    m_intf = intf;

  } // Bloom::registerInterfaces

} // visualizer

Q_EXPORT_PLUGIN2( bloom, visualizer::Bloom );
