#ifndef TREASUREDATA_H
#define TREASUREDATA_H

#include "../lib/gocfamily_data.h"
#include "../lib/parser/parser.h"

struct TreasureDataInfo
{
  int x;
  int y;
  int gold; 
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
