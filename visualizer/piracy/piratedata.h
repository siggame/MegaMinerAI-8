#ifndef PIRATEDATA_H
#define PIRATEDATA_H

#include "../lib/gocfamily_data.h"
#include "../lib/parser/parser.h"

struct PirateDataInfo
{
  int owner;
  float x;
  float y;
};

class PirateData : public GOCFamily_Data<PirateDataInfo>
{
public:
  PirateData();
  ~PirateData();

  void update();
  const GOC_IDType componentID() const;
  void parsePirate( const Game& game, int pirateId );
private:
};

#endif
