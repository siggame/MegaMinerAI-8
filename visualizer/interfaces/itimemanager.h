#ifndef ITIMEMANAGER_H
#define ITIMEMANAGER_H

#include "../lib/updateneeded.h"
#include <QtPlugin>
#include <QMutex>

namespace visualizer
{

class ITimeManager
{    
  public:

    enum mode
    {
      Play = 0,
      Pause = 1,
      Stop = 1,                  // Don't feel the need to differentiate at this point
      Rewind = 2
    };

  public:
    virtual const int& getTurn() = 0;
    virtual const int& getFrame() = 0;
    virtual void setTurn( const int& turn ) = 0;

    virtual const int& getNumTurns() = 0;
    virtual void setNumTurns( const int& numTurns ) = 0;

    virtual float getSpeed() = 0;
    virtual void setSpeed( const float& speed ) = 0;

    virtual int timeHash() = 0;
    virtual mode getMode() = 0;

    virtual void updateFrames() = 0;
    virtual void start() = 0;
    virtual void timerStart() = 0;

    virtual void requestUpdate( UpdateNeeded* requester ) = 0;
    virtual void updateChildren() = 0;

    virtual QMutex& getMutex() = 0;

};

} // visualizer

Q_DECLARE_INTERFACE( visualizer::ITimeManager, "siggame.vis2.timemanager/0.1" );

#endif
