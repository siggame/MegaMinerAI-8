#ifndef PIRACYSTACK_H
#define PIRACYSTACK_H

#include <string.h>
#include <vector>
#include "parser/structures.h"
#include "animatable.h"
#include "irenderer.h"

namespace visualizer
{
  struct PirateData: public AnimData
  {
    float x;
    float y;
  };

  struct Stack: public Animatable
  {
    public:
      Stack( IRenderer* renderer ) : Animatable( renderer )
      {
        m_owner = m_pirates =
        m_ships = m_ports = 
        m_health = m_maxHealth =
        m_strength = m_maxStrength =
        m_gold = 0;
      }

      void updateAnim( const std::vector<Animation*>& animList );

      AnimData *getData()
      {
        return &m_pirateData;
      }

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

      // Animation x and y
      float a_x;
      float a_y;

      PirateData m_pirateData;

  };


} // visualizer

#endif 
