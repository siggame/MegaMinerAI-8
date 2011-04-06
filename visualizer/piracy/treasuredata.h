#ifndef TREASUREDATA_H
#define TREASUREDATA_H

#include "../lib/gocfamily_data.h"
#include "../lib/parser/parser.h"

struct TreasureDataInfo
{
  int x;
  int y;
  int pirateID; //Pirate carrying treasure, 0 if not carried (lying on ground)
  int amount; 
};

class TreasureData : public GOCFamily_Data<TreasureDataInfo>
{
public:
  TreasureData();
  ~TreasureData();

  void update();
  const GOC_IDType componentID() const;
  void parseTreasure( const Game& game, int treasureId );
private:
};

#endif
