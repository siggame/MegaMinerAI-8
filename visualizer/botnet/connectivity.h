#ifndef CONNECTIVITY_H
#define CONNECTIVITY_H

#include <map>
#include <vector>
#include <stack>
#include <iostream>
#include "models.h"
using namespace std;

namespace visualizer
{

  class ConnectivityNode
  {
    public:
      ConnectivityNode()
      {
        m_connected = false;
      }

      const bool& connected() const
      {
        return m_connected;
      }

      void setConnected( const bool& c )
      {
        m_connected = c;
      }

    private:
      bool m_connected;

  }; // ConnectivityNode

  class Connectivity
  {

    public: 
      void addBase( const float& x, const float& y );
      void addNode( const float& x, const float& y, ConnectivityNode* node );
      void generateConnectivity();
      
      int numConnectedNodes;
      int numUnconnectedNodes;

    private:
      bool findMyNode( const vertex& c );
    
      std::map<vertex, ConnectivityNode*> m_nodes;
      std::vector<vertex> m_bases;
      

  }; // Connectivity

  ostream& operator << ( ostream& os, const vertex& rhs );
  

} // visualizer
#endif
