#ifndef LIGHT_REVELATION_H
#define LIGHT_REVELATION_H

#include <QObject>
#include "igame.h"
#include "animsequence.h"

namespace visualizer
{

  class LightRevelation: public QObject, public AnimSequence, public IGame
  {
    Q_OBJECT;
    Q_INTERFACES( visualizer::IGame );
    public: 
      LightRevelation();
      ~LightRevelation();

      LogRegex logFileInfo();
      void loadGamelog( std::string gamelog );

  }; 

} // visualizer

#endif // LIGHT_REVELATION_H
