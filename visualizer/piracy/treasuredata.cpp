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

void TreasureData::parseTreasure( const Game& game, int treasureId )
{
  for( int i = 0; i < game.states.size(); i++ )
  {
    std::map<int,Treasure>::const_iterator j = game.states[i].treasures.find( treasureId );
    if( j != game.states[i].treasures.end() )
    {
      TreasureDataInfo t;
      t.x = j->second.x;
      t.y = j->second.y;
      t.pirateID = j->second.pirateID;
      t.amount = j->second.amount;
      //cout << "Turn: " << i << ", X: " << t.x << ", Y: " << t.y << endl;
      m_timeline.add( i, 0, t );
    }
  }
}
