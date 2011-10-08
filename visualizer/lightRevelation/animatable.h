#ifndef ANIMATABLE_H
#define ANIMATABLE_H

#include "animatable.h"
#include "irenderer.h"

namespace visualizer
{
  struct image: public Animatable
  {
    image( IRenderer *render ) : Animatable( render )
    {}

    string fileName;

    AnimData* getData()
    {
      return 0;
    }

  };

} // visualizer

#endif // ANIMATABLE_H
