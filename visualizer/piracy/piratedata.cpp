#include "piratedata.h"

PirateData::PirateData()
{
}


PirateData::~PirateData()
{
}

const GOC_IDType PirateData::componentID() const
{
  return GOC_IDType( "GOCDataPirate" );
}

void PirateData::update()
{
}

void PirateData::parsePirate( const Game& game, int pirateId )
{
  for( int i = 0; i < game.states.size(); i++ )
  {
    std::map<int,Pirate>::const_iterator j = game.states[i].pirates.find( pirateId );
    if( j != game.states[i].pirates.end() )
    {
      PirateDataInfo t;
      t.owner = j->second.owner;
      t.x = j->second.x;
      t.y = j->second.y;
      m_timeline.add( i, 0, t );
    }
  }
}
