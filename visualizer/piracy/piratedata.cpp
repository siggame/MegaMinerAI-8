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
      t.totalHealth += j->second.health;
      t.totalStrength += j->second.strength;
      t.hasMoved = j->second.hasMoved;
      t.hasAttacked = j->second.hasAttacked;
      //cout << "Turn: " << i << ", X: " << t.x << ", Y: " << t.y << endl;
      m_timeline.add( i, 0, t );
    }
  }
}

void PirateData::addPirateStack(const PirateDataInfo & info, const int & turn, const int & frame)
{
  m_timeline.add(turn, frame, info);
}
