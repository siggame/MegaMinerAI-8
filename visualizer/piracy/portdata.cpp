#include "portdata.h"

const GOC_IDType PortData::componentID() const
{
	return GOC_IDType("GOCDataPort");
}


void PortData::parsePort( const Game& game, int portId, int turn )
{
	std::map<int,Port>::const_iterator j = game.states[turn].ports.find( portId );
	if( j != game.states[turn].ports.end() )
	{
		m_data.x = j->second.x;
		m_data.y = j->second.y;
		m_data.owner = j->second.owner;
	}
}
