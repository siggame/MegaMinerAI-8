#ifndef PIRACY_H
#define PIRACY_H

#include "igame.h"
#include "parser/parser.h"
#include "parser/structures.h"

#include <QThread>

namespace visualizer 
{

  class Piracy: public QThread, public visualizer::IGame
  {
    Q_OBJECT;
    Q_INTERFACES( visualizer::IGame );
    public:
      LogRegex logFileInfo();
      void loadGamelog( std::string gamelog );
      void registerInterfaces( Interfaces intf );

      void run();

    private:
      Game *m_game;
      
      Interfaces m_intf;
  };

} // visualizer

#endif
