#ifndef BLOOM_H
#define BLOOM_H

#include <QThread>
#include "common.h"
#include "parser/parser.h"
#include "parser/structures.h"
#include "igame.h"

#include "animsequence.h"

namespace visualizer
{

  class BotNet: public QThread, public IGame
  {
    Q_OBJECT;
    Q_INTERFACES( visualizer::IGame );
    public: 
      BotNet();
      ~BotNet();

      void run();

      LogRegex logFileInfo();
      void loadGamelog( std::string gamelog );
      size_t checkForMovement( Game* g, const size_t& state, const int& id );

    private:
      Game *m_game;
      AnimSequence *m_timeline;

      QMutex m_suicideMutex;
      bool m_suicide;
  }; 

} // visualizer


#endif // BLOOM_H
