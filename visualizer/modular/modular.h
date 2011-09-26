#ifndef MODULAR_H
#define MODULAR_H

#include <QObject>
#include "parser/parser.h"
#include "parser/structures.h"
#include "igame.h"
#include "animsequence.h"

namespace visualizer
{
  class Modular: public QObject, public AnimSequence, public IGame
  {
      Q_OBJECT;
      Q_INTERFACES( visualizer::IGame );

      public:
        Modular();
        ~Modular();

        LogRegex logFileInfo();
        void loadGamelog( std::string gamelog );
	  
	private:
	  Game *m_game;
  };
}
#endif
