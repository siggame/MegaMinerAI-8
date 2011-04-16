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


void BoatData::parseBoat( const Game& game, int boatId, int turn)
{
	std::map<int,Ship>::const_iterator j = game.states[turn].ships.find(boatId);
	if( j != game.states[turn].ships.end() )
	{
		m_data.owner = j->second.owner;
		m_data.x = j->second.x;
		m_data.y = j->second.y;
	}
}
