#ifndef VIRUSES_H
#define VIRUSES_H

#include "animatable.h"
#include "irenderer.h"

namespace visualizer
{ 
  struct VirusData: public AnimData
  {
    float x;
    float y;
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

  struct tile: public Animatable
  {
    tile( IRenderer *renderer ) : Animatable( renderer )
    { owner = id = x = y = 0; }

    int id;
    int owner;
    float x;
    float y;

    AnimData* getData()
    {
      return 0;
    }


  };

} // visualizer

#endif // VIRUSES_H
