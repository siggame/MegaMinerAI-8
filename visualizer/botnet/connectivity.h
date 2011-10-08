#ifndef CONNECTIVITY_H
#define CONNECTIVITY_H

#include <map>
#include <vector>
#include <stack>

namespace visualizer
{

  struct coord
  {
    coord()
    {
      x = y = 0;
    }

    coord( const coord& rhs )
    {
      x = rhs.x;
      y = rhs.y;
    }

    coord( const float& X, const float& Y )
    {
      x = X;
      y = Y;
    }

    bool operator > ( const coord& rhs ) const
    {
      if( x > rhs.x )
        return true;
      if( y > rhs.y )
        return true;

      return false;
    }

    bool operator < ( const coord& rhs ) const
    {
      if( x < rhs.x )
        return true;
      if( y < rhs.y )
        return true;

      return false;
    }

    coord operator + ( const coord& rhs )
    {
      coord r;
      r.x = x + rhs.x;
      r.y = y + rhs.y;

      return r;
    }
    
    float x;
    float y;

  };

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

    private:
      bool findMyNode( const coord& c );
    
      std::map<coord, ConnectivityNode*> m_nodes;
      std::vector<coord> m_bases;
      

  }; // Connectivity

} // visualizer

#endif // CONNECTIVITY_H
