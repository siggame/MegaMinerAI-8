#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

#include <QTimer>
#include <QTime>
#include <time.h>
#include <list>

#include "../../interfaces/itimemanager.h"

namespace visualizer
{

class _TimeManager : public QObject, public ITimeManager
{
  Q_OBJECT
  Q_INTERFACES( visualizer::ITimeManager );
  public:
    static void setup();
    static void destroy();
    void _setup();

    void updateProgress( float progress );

    float getSpeed();
    void setSpeed( const float& speed );

    void timerStart();
    void start();

    void requestUpdate( UpdateNeeded* requester );
    void updateChildren();

    // @NOTE These four will probably have their names changed
    void setTurn( const int& turn );
    const int& getTurn();

    const int& getNumTurns();
    void setNumTurns( const int& numTurns );

  private slots:
    void timerUpdate();

  private:
    QTimer *m_timer;
    QTime m_time;
    float m_speed;
    float m_progress;
    int m_turn;
    int m_numTurns;
    int m_lastTime;
    std::list< UpdateNeeded* > m_updateRequesters;
};

extern _TimeManager *TimeManager;

} // visualizer

#endif
