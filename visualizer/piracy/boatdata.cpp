#include "boatdata.h"

BoatData::BoatData()
{
}

BoatData::~BoatData()
{
}

const GOC_IDType BoatData::componentID() const
{
  return GOC_IDType( "GOCDataBoat" );
}

void BoatData::update()
{
}

void BoatData::parseBoat( const Game& game, int boatId )
{
  for( int i = 0; i < game.states.size(); i++ )
  {
    std::map<int,Ship>::const_iterator j = game.states[i].ships.find(boatId);
    if( j != game.states[i].ships.end() )
    {
      BoatDataInfo t;
      t.owner = j->second.owner;
      t.x = j->second.x;
      t.y = j->second.y;
      m_timeline.add( i, 0, t );
    }
  }
}


