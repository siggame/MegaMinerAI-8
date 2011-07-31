#ifndef PIRACYSTACK_H
#define PIRACYSTACK_H

#include <string.h>
#include <vector>
#include "parser/structures.h"
#include "../interfaces/ianimationengine.h"

namespace visualizer
{
  struct Stack: public Animator
  {
    public:
      Stack()
      {
        // Set everything in here to 0
        // Not sure how this reacts to m_ids
        memset( this, 0, sizeof( Stack ) );
      }

      void updateAnim( const std::vector<Animation*>& animList );

      int m_owner;
      int m_pirates;
      int m_ships;
      int m_ports;

      int m_health;
      // This can probably be derived
      int m_maxHealth;

      int m_strength;
      // I don't even know what this is
      int m_maxStrength;

      int m_gold;

      // Pirate IDs and stuff
      std::vector<int> m_pirateIds;
      std::vector<int> m_shipIds;
      std::vector<int> m_portIds;
      std::vector<int> m_goldIds;

      float m_x;
      float m_y;
  };


} // visualizer

#endif 
