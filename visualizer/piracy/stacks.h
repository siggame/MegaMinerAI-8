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
  public:
    enum _Move
    {
      Left,
      Right,
      Up,
      Down
    };

  private: 
    vector<_Move> m_moves;
    float m_x; 
    float m_y;

  public:
    MoveList( const float& x, const float& y, const vector<_Move>& moves )
    {
      m_x = x;
      m_y = y;

      m_moves = moves;
    }

    bool operator < ( const MoveList& moveList ) const
    {
      size_t s1 = m_moves.size();
      size_t s2 = moveList.m_moves.size();
      if( s1 == s2 )
      {
        if( moveList.m_x == m_x )
        {
          if( moveList.m_y == m_y )
          {
            for( size_t i = 0; i < s1; i++ )
            {
              if( m_moves[ i ] < moveList.m_moves[ i ] )
              {
                return true;
              }
            }
          }
          else
          {
            return m_y < moveList.m_y;
          }
        }
        else
        {
          return m_x < moveList.m_x;
        }
      } else
      {
        return s1 < s2;
      }

      return false;
    }

    bool operator == ( const MoveList& moveList ) const
    {
      size_t s1 = m_moves.size();
      size_t s2 = moveList.m_moves.size();
      if( s1 == s2 )
      {
        if( moveList.m_x == m_x )
        {
          if( moveList.m_y == m_y )
          {
            for( size_t i = 0; i < s1; i++ )
            {
              if( m_moves[ i ] != moveList.m_moves[ i ] )
              {
                return false;
              }
            }
            return true;
          }
        }
      }

      return false;
    }

    bool operator != ( const MoveList& moveList ) const
    {
      return !(*this == moveList);
    }

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
    // Get stack will search for the existing stack
    // or create a new one if necessary
    stackType& getStack( key& index );

  private:
    // This represents the map which will point to a particular point in the 
    // list
    std::map<key, stackType*, compare > m_stackMap;
    // This represents all the stacks that are present in the current frame.
    std::vector<stackType> m_stacks;

  };
    
  class Stack
  {

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
