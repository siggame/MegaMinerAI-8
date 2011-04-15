#include "treasuredata.h"

TreasureData::TreasureData()
{
}


TreasureData::~TreasureData()
{
}

const GOC_IDType TreasureData::componentID() const
{
  return GOC_IDType( "GOCDataTreasure" );
}

void TreasureData::update()
{
}
#include <iostream>
using namespace std;

void TreasureData::parseTreasure( const Game& game, int treasureId, int turn )
{
    std::map<int,Treasure>::const_iterator j = game.states[turn].treasures.find( treasureId );
    if( j != game.states[turn].treasures.end() )
    {
      m_data.x = j->second.x;
      m_data.y = j->second.y;
      m_data.gold = j->second.gold;
    }
}
