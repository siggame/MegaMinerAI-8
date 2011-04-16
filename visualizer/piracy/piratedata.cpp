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


#include <iostream>
using namespace std;

void PirateData::parsePirate( const Game& game, int pirateId, int turn )
{
	std::map<int,Pirate>::const_iterator j = game.states[turn].pirates.find( pirateId );
	if( j != game.states[turn].pirates.end() )
	{
		m_data.owner = j->second.owner;
		m_data.x = j->second.x;
		m_data.y = j->second.y;
		m_data.totalHealth += j->second.health;
		m_data.totalStrength += j->second.strength;
		m_data.movesLeft = j->second.movesLeft;
		m_data.attacksLeft = j->second.attacksLeft;
		m_data.totalGold += j->second.gold;
	}
}


void PirateData::addPirateStack(const PirateDataInfo & info, const int & turn, const int & frame)
{
	std::cout << "turn: " << turn << " frame: " << frame <<'\n';
	//m_timeline.add(turn, frame, info);
}
