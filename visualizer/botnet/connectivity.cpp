#include "connectivity.h"


namespace visualizer
{
  void Connectivity::addBase( const float& x, const float& y )
  {
    m_bases.push_back( coord( x, y ) );

  } // Connectivity::addBase()

  void Connectivity::addNode( const float& x, const float& y, ConnectivityNode *node )
  {
    m_nodes[ coord( x, y ) ] = node;
    
  } // Connectivity::addNode()

  bool Connectivity::findMyNode( const coord& c )
  {
    std::map<coord, ConnectivityNode*>::iterator i = m_nodes.find( c );
    if( i != m_nodes.end() ) 
    {
      if( !i->second->connected() )
      {
        return true;
      }
    }
    return false;

  } // Connectivity::findMyNode()

  coord udlr[] = 
  {
    coord( 1, 0 ),
    coord( 0, 1 ),
    coord( -1, 0 ),
    coord( 0, -1 )
  };

  void Connectivity::generateConnectivity()
  {

    for( std::vector<coord>::iterator i = m_bases.begin(); i != m_bases.end(); i++  )
    {
      std::stack<coord> nodesLeft;
      for( size_t j = 0; j < 4; j++ )
      {
        if( findMyNode( *i + udlr[ j ] ) )
        {
          nodesLeft.push( *i + udlr[ j ] );
        }
      }

      while( nodesLeft.size() )
      {
        coord c = nodesLeft.top();
        nodesLeft.pop();

        if( m_nodes[ c ]->connected() ) 
          continue;

        m_nodes[ c ]->setConnected( true );

        for( size_t j = 0; j < 4; j++ )
        {
          if( findMyNode( c + udlr[ j ] ) )
          {
            nodesLeft.push( c + udlr[ j ] );
          }
        }

      }
      
    }

  } // Connectivity::generateConnectivity()

  ostream& operator << ( ostream& os, const coord& rhs )
  {
    os << "( " << rhs.x << ", " << rhs.y << " )";
    return os;

  }

} // visualizer

