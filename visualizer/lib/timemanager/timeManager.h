#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

#include "../singleton.h"

class TimeManager : public Singleton<TimeManager>
{
  public:
    int getTurn();
    int getFrame();
    void setTurn(int);
#if 0
    operator++();
    operator++ (int);
    operator--();
    operator-- (int);
#endif

  private:
    int m_turn;
    int m_frame;
    //const float m_turnRate = 2; // turns per second
};

#if 0
class timeManagerSingleton : public Singleton <timeManager>
{
  public:
		int intAccessor()
		{
			if (isInit())
			{
				//return get()->m_intVar;
			}
			return 0;
		}
};
#endif

#endif
