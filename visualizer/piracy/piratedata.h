#ifndef PIRATEDATA_H
#define PIRATEDATA_H

#include "../lib/gocfamily_data.h"
#include "../lib/parser/parser.h"
#include <list>

struct PirateDataInfo
{
  int owner;
  int x;
  int y;
  int totalHealth; 
  int numPirates;
  int totalStrength;
  int hasMoved;
  int hasAttacked;
  std::list<int> piratesInStack;
  
  PirateDataInfo()
  {
  	owner = 0;
	  x = 0;
	  y = 0;
	  totalHealth = 0; 
  	numPirates = 0;
    totalStrength = 0;
  	hasMoved = 0;
  	hasAttacked = 0;
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
};

#endif
