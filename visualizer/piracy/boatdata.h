#ifndef BOATDATA_H
#define BOATDATA_H

#include "../lib/gocfamily_data.h"
#include "../lib/parser/parser.h"


struct BoatDataInfo
{
  int owner;
  float x;
  float y;
};

class BoatData : public GOCFamily_Data<BoatDataInfo>
{
public:
  BoatData();
  ~BoatData();

  void update();
  const GOC_IDType componentID() const;   
  void parseBoat( const Game& game, int boatId, int turn);

private:
};


#endif
