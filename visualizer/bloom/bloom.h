#ifndef BLOOM_H
#define BLOOM_H

#include "igame.h"
#include "animsequence.h"
#include <QThread>

namespace visualizer
{
  class Bloom: public QThread, public AnimSequence, public visualizer::IGame
  {
    Q_OBJECT;
    Q_INTERFACES( visualizer::IGame );
    public:
      Bloom();
      ~Bloom();

      LogRegex logFileInfo();
      void loadGamelog( std::string gamelog );
      void registerInterfaces( Interfaces intf );
  }; // Bloom

} // visualizer

#endif
