#ifndef VIRUSES_H
#define VIRUSES_H

#include "animatable.h"
#include "irenderer.h"
#include "connectivity.h"

namespace visualizer
{ 

  struct GeneralAnim: public AnimData
  {
    float alpha;
  };

  struct VirusData: public GeneralAnim
  {
    float x;
    float y;
  };

  struct moveBoard: public Animatable
  {
    moveBoard( IRenderer *renderer ) : Animatable( renderer )
    {}

    float offst;

    AnimData* getData()
    {
      return 0;
    }
  };

  struct virus: public Animatable
  {
    virus( IRenderer *renderer ) : Animatable( renderer )
    { owner = level = movesLeft = id = x = y = 0; }

    int id;
    int owner;
    int level;
    int movesLeft;
    float x;
    float y;

    AnimData* getData()
    {
      return &m_virusData;
    }

    VirusData m_virusData;
    
    
  }; // Virus

  struct base: public Animatable
  {
    base( IRenderer *renderer ) : Animatable( renderer )
    { owner = id = x = y = 0; }

    int id;
    int owner;
    float x;
    float y;

    AnimData* getData()
    {
      return &g;
    }

    GeneralAnim g;

  }; // base

  struct tile: public Animatable, public ConnectivityNode
  {
    tile( IRenderer *renderer ) : Animatable( renderer )
    { owner = id = x = y = 0; }

    int id;
    int owner;
    float x;
    float y;

    AnimData* getData()
    {
      return &g;
    }

    GeneralAnim g;

  }; // tile
  
  struct background: public Animatable
  {
    background( IRenderer *renderer ) : Animatable( renderer )
    { }
    
    int mapWidth;
    int mapHeight;
    
    AnimData* getData()
    {
      return NULL;
    }
  }; // background
  
  struct grid: public Animatable
  {
    grid( IRenderer *renderer ) : Animatable( renderer )
    { }
    
    int mapWidth;
    int mapHeight;
    
    int pixelHeight;
    int pixelWidth;
    
    AnimData* getData()
    {
      return NULL;
    }
  }; // grid

  struct scoreboard: public Animatable
  {
    scoreboard( IRenderer* renderer ) : Animatable( renderer )
    { }

    float x, y;

    int player;
    int score;

    AnimData* getData()
    { 
      return 0;
    }

  };

} // visualizer

#endif // VIRUSES_H
