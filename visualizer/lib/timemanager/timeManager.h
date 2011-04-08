#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

#include <QTimer>
#include <time.h>
#include "../singleton.h"

class TimeManager : public QObject, public Singleton<TimeManager>
{
  Q_OBJECT
  public:
    static const int& getTurn();
    static const int& getFrame();
    static void setTurn( const int& turn );

    static const int& getNumTurns();
    static void setNumTurns( const int& numTurns );

    static const int& getSpeed();
    static void setSpeed( const int& speed );


    static void create();
    void setup();

    void updateFrames();

    enum mode
    {
      Play = 0,
      Pause = 1,
      Stop = 1, // Don't feel the need to differentiate at this point
      Rewind = 2
    };
  private slots:
    void timerUpdate();

  private:
    int m_turn;
    int m_numTurns;
    int m_frame;
    int m_framesPerTurn;
    mode m_mode;

    QTimer *timer;

    int m_speed;
    int m_lastTime;
};


#endif
