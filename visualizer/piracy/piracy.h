#ifndef PIRACY_H
#define PIRACY_H

#include "igame.h"

class Piracy: public QObject, public IGame
{
  Q_OBJECT
  Q_INTERFACES( IGame );
  public:
    LogRegex logFileInfo();
    void loadGamelog( std::string gamelog );

};

#endif
