#include "../singleton.h"

class timeManager
{
  public:
    int getTurn();
    int getFrame();
    void setTurn(int);
    /*operator++;
    operator++ (int);
    operator--;
    operator-- (int);*/

  private:
    int m_turn;
    int m_frame;
    //const float m_turnRate = 2; // turns per second
};

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
