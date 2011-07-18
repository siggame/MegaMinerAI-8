#ifndef STACKS_H
#define STACKS_H

#include <vector>
#include <map>
#include <list>
using namespace std;

namespace visualizer
{
  class MoveList
  {
  private: 
    enum Move
    {
      Left,
      Right,
      Up,
      Down
    };

    vector<Move>      m_moves;
  public:
    bool operator < ( const MoveList& moveList );
    bool operator == ( const MoveList& moveList );
  };

  class Stack
  {
  private:
    MoveList m_moveList;
  public:
    
  };

  class Turn
  {
  public:
    map<MoveList, Stack, less<MoveList> > m_stacks;
    
  };

  class Timeline
  {
  public: 
  // Make sure this is thread safe so we can do realtime loading.
  // We need to order items by the number of turns they have for 
  // Turn by turn mode and simultaneous turn mode.  
    void addTurn( const Turn& turn );

  };

}

#endif
