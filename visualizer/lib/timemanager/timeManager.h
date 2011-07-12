#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

#include <QTimer>
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

    _TimeManager()
    {
      m_sleepTime = -1;
      m_awakeTime = -2;
    }

    const int& getTurn();
    const int& getFrame();
    void setTurn( const int& turn );

    const int& getNumTurns();
    void setNumTurns( const int& numTurns );

    float getSpeed();
    void setSpeed( const float& speed );

    int timeHash();
    mode getMode();

    static void setup();
    static void destroy();
    void _setup();

    void updateFrames();
    void start();
    void timerStart();

    void requestUpdate( UpdateNeeded* requester );
    void updateChildren();

  private slots:
    void timerUpdate();

  private:
    int m_turn;
    int m_numTurns;
    int m_frame;
    int m_framesPerTurn;
    mode m_mode;

    QTimer *timer;

    float m_speed;
    int m_lastTime;
    int m_hash;
    int m_sleepTime;
    int m_awakeTime;
    int m_time;

    std::list< UpdateNeeded* > m_updateRequesters;
};

extern _TimeManager *TimeManager;

} // visualizer

#endif
