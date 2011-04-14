#ifndef PIRATEDATA_H
#define PIRATEDATA_H

#include "../lib/gocfamily_data.h"
#include "../lib/parser/parser.h"
#include <list>
#include "renderdata.h"

struct PirateDataInfo : public RenderDataInfo
{
  int owner;
  int x;
  int y;
  int totalHealth; 
  int numPirates;
  int totalStrength;
  int movesLeft;
  int attacksLeft;
  int totalGold;
  std::list<int> piratesInStack;

  void clear()
  {
   	owner = 0;
	  x = 0;
	  y = 0;
	  totalHealth = 0; 
  	numPirates = 0;
    totalStrength = 0;
  	movesLeft = 0;
  	attacksLeft = 0; 
  	totalGold = 0;
    piratesInStack.clear();
  }
  
  PirateDataInfo()
  {
    clear();
  }
};



class PirateData : public GOCFamily_Data<PirateDataInfo>
{
public:
  PirateData();
  ~PirateData();
  void addPirateStack(const PirateDataInfo &, const int &, const int &);

  void update();
  const GOC_IDType componentID() const;
  void parsePirate( const Game& game, int pirateId );

private:

  RenderData<PirateDataInfo> *m_renderData;
};

#endif
