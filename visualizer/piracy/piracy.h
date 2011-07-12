#ifndef PIRACY_H
#define PIRACY_H

#include "igame.h"

namespace visualizer 
{

class Piracy: public QObject, public IGame
{
  Q_OBJECT
  Q_INTERFACES( visualizer::IGame );
  public:
    LogRegex logFileInfo();
    void loadGamelog( std::string gamelog );
    void registerInterfaces( Interfaces intf );

  private:
    Interfaces m_intf;
};

} // visualizer

#endif
