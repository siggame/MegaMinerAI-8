#include "shipdata.h"



const GOC_IDType ShipData::componentID() const
{
    return GOC_IDType("GOCDataShip");
}
void ShipData::parseShip( const Game& game, int shipId, int turn )
{
    std::map<int,Ship>::const_iterator j = game.states[turn].ships.find( shipId );
    if( j != game.states[turn].ships.end() )
    {
      m_data.x = j->second.x;
      m_data.y = j->second.y;
      //m_data.owner = j->second.owner;
    }
}
