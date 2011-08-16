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
    virtual const int& getTurn() = 0;
    virtual const float& getTurnPercent() = 0;
    virtual const int& getNumTurns() = 0;

    virtual void setNumTurns( const int& numTurns ) = 0;

    virtual void requestUpdate( UpdateNeeded* requester ) = 0;

    virtual void updateProgress( float progress ) = 0;

    virtual const int& nextTurn() = 0;
    virtual const int& prevTurn() = 0;

    virtual void play() = 0;
    virtual void pause() = 0;
    
    virtual void fastForward() = 0;
    virtual void rewind() = 0;

    /// @TODO Determine whether the visualizer should have exclusive
    /// ability to change speed.
#if 0
    virtual void setTurn( const int& turn ) = 0;
    virtual float getSpeed() = 0;
    virtual void setSpeed( const float& speed ) = 0;
#endif


};

} // visualizer

Q_DECLARE_INTERFACE( visualizer::ITimeManager, "siggame.vis2.timemanager/0.1" );

#endif
