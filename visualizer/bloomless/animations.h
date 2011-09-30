#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include "plant.h"
#include "irenderer.h"

namespace visualizer
{

  struct StartAnim: public Anim
  {
    public:
      void animate( const float& t, AnimData *d );


      float controlDuration() const
      {
        return 0;
      }

      float totalDuration() const
      {
        return 0;
      }
  };

  struct DrawPlant: public Anim
  {
    DrawPlant( plant *p )
    {
      m_plant = p;
    }

    void animate( const float& t, AnimData* d);
    
    float controlDuration() const
    {
      return 0;
    }

    float totalDuration() const
    {
      return 0;
    }

    private:
      plant* m_plant;

  };

}

#endif // ANIMATION_H
