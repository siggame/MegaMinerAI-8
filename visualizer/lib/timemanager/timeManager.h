#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

#include <time.h>
#include "../singleton.h"

class TimeManager : public Singleton<TimeManager>
{
  public:
    static const int& getTurn();
    static const int& getFrame();
    static void setTurn( const int& turn );

    static const int& getSpeed();
    static void setSpeed( const int& speed );

    static void create();

    void updateFrames();

    enum mode
    {
      Play = 0,
      Pause = 1,
      Stop = 1, // Don't feel the need to differentiate at this point
      Rewind = 2
    };

  private:
    int m_turn;
    int m_frame;
    int m_framesPerTurn;
    mode m_mode;

    int m_speed;
    clock_t m_lastTime;
};


#endif
