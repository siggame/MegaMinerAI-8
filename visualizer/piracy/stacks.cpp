#include "stacks.h"

namespace visualizer
{

  bool MoveList::operator == ( const MoveList& moveList )
  {
    size_t sizeThis = m_moves.size();
    size_t sizeThat = moveList.m_moves.size();

    if( sizeThis == sizeThat )
    {
      for( int i = 0; i < sizeThis; i++ )
      {
        if( m_moves[ i ] != moveList.m_moves[ i ] )
        {
          return false;
        }
      }
    } 
    else
    {
      return false;
    }

    return true;
  }

  bool MoveList::operator < ( const MoveList& moveList )
  {
    size_t sizeThis = m_moves.size();
    size_t sizeThat = moveList.m_moves.size();

    if( sizeThis == sizeThat )
    {
      for( int i = 0; i < sizeThis; i++ )
      {
        if( m_moves[ i ] < moveList.m_moves[ i ] )
        {
          return true;
        }
      }
    } else
    {
      return sizeThis < sizeThat;
    }

    return false;
  }

}
