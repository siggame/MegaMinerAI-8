#ifndef PLANT_H
#define PLANT_H

#include "animatable.h"
#include "irenderer.h"

namespace visualizer
{
  struct plant: public Animatable
  {
    plant( IRenderer *render ) : Animatable( render )
    {}

    int objectID;
    float x, y;
    int ownerID;
    bool root, flower, leaf;
    int health;

    AnimData* getData()
    {
      return 0;
    }

  };

} // visualizer

#endif // PLANT_H
