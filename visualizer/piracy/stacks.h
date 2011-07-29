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
    float m_x; 
    float m_y;
  public:
    MoveList( const float& x, const float& y, const vector<Move>& moves )
    {
      m_x = x;
      m_y = y;

      m_moves = moves;
    }

    bool operator < ( const MoveList& moveList );
    bool operator == ( const MoveList& moveList );
  };


// Ok here's what I'm thinking.
// We use a map to categorize where units go in a stack
// We actually store the stacks in a list for easy iterating
// The map will point to the list where the unit should go.
// If we need even more of a speed increase we use a 2D array
// which will point to the maps which will point the lists. 
// When rendering, the only thing that will/should exist is the list.
// The maps would no longer be needed, and, as a result, neither
// would the 2d array.

template<class key, class stackType, class compare = less<key> >
class StackOrganizer
{
public:
  

private:
  // This represents the map which will point to a particular point in the 
  // list
  typedef typename list<stackType>::iterator* stackList;
  std::map<key, stackList, compare > m_stackMap;
  // This represents all the stacks that are present in the current frame.
  std::list<stackType> m_stacks;

};
  
#if 0
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

#endif
}

#include "stacks.hpp"

#endif
