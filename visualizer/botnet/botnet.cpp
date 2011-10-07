#include "frame.h"
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
    cout << "Load Bloom Gamelog" << endl;
  } // BotNet::loadGamelog() 

} // visualizer

Q_EXPORT_PLUGIN2( botnet, visualizer::BotNet );
