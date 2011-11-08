#include "connectivity.h"


namespace visualizer
{
  void Connectivity::addBase( const float& x, const float& y )
  {
    m_bases.push_back( vertex( x, y ) );

  } // Connectivity::addBase()

  void Connectivity::addNode( const float& x, const float& y, ConnectivityNode *node )
  {
    m_nodes[ vertex( x, y ) ] = node;
    
  } // Connectivity::addNode()

  bool Connectivity::findMyNode( const vertex& c )
  {
    std::map<vertex, ConnectivityNode*>::iterator i = m_nodes.find( c );
    if( i != m_nodes.end() ) 
    {
      if( !i->second->connected() )
      {
        return true;
      }
    }
    return false;

  } // Connectivity::findMyNode()

  vertex udlr[] = 
  {
    vertex( 1, 0 ),
    vertex( 0, 1 ),
    vertex( -1, 0 ),
    vertex( 0, -1 )
  };

  void Connectivity::generateConnectivity()
  {

    for( std::vector<vertex>::iterator i = m_bases.begin(); i != m_bases.end(); i++  )
    {
      std::stack<vertex> nodesLeft;
      nodesLeft.push( *i );
      
      while( nodesLeft.size() )
      {
        vertex c = nodesLeft.top();
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
    
    numConnectedNodes = 0;
    numUnconnectedNodes = 0;
    for(map<vertex, ConnectivityNode*>::iterator i = m_nodes.begin(); i != m_nodes.end(); i++)
    {
      if(i->second->connected())
        numConnectedNodes++;
      else
        numUnconnectedNodes++;
    }

  } // Connectivity::generateConnectivity()

  ostream& operator << ( ostream& os, const vertex& rhs )
  {
    os << "( " << rhs.x << ", " << rhs.y << " )";
    return os;

  }

} // visualizer

