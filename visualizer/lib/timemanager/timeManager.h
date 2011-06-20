#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

#include <QTimer>
#include <time.h>
#include <list>
#include "../singleton.h"

class UpdateNeeded
{
public:
  virtual void update() = 0;
};

class TimeManager : public QObject, public Singleton<TimeManager>
{
  Q_OBJECT
  public:
 
    TimeManager()
    {
      m_sleepTime = -1;
      m_awakeTime = -2;
    }
    enum mode
    {
      Play = 0,
      Pause = 1,
      Stop = 1, // Don't feel the need to differentiate at this point
      Rewind = 2
    };   
    
    static const int& getTurn();
    static const int& getFrame();
    static void setTurn( const int& turn );

    static const int& getNumTurns();
    static void setNumTurns( const int& numTurns );

    static const float& getSpeed();
    static void setSpeed( const float& speed );

    static int timeHash();
    static mode getMode();

    static bool create();
    void setup();

    void updateFrames();
    void start();
    static void timerStart();

    static void requestUpdate( UpdateNeeded* requester );
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

#endif
