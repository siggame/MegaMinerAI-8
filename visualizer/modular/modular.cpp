#include "modular.h"

namespace visualizer
{
  Modular::Modular()
  {
    m_game = 0;
  }
  
  Modular::~Modular()
  {
    delete m_game;
  }
  
  LogRegex Modular::logFileInfo()
  {
    LogRegex lr;
    lr.regex = "(\"megaminer\" 6)";
    lr.startSize = 50;
	return lr;
  }
  
  void Modular::loadGamelog(std::string gamelog)
  {
    cout << "Load Modular Gamelog" << endl;
	
	delete m_game;
	
	m_game = new Game;
	
        if (!parseFile( *m_game, (char*)gamelog.c_str() ) )
	{
	  delete m_game;
          THROW
          ( GameException,"Cannot load gamelog: %s",gamelog.c_str() );
	} //if (parseFile( *m_gate, (char*)gamelog.c_str() ) );

  } //void Modular::loadGamelog(std::string gamelog)
  
} //namespace visualizer

Q_EXPORT_PLUGIN2( modular, visualizer::Modular);
