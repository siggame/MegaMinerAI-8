#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include "plant.h"

namespace visualizer
{

  class StartAnim: public Anim
  {
    public:
      StartAnim( plant* p )
      {
        m_plant = p;
      }

      void animate( const float& t, AnimData *d );
      float controlDuration() const
      { return 0; }
      float totalDuration() const
      { return 1; }
    private:
      plant* m_plant;

  }; // StartAnim

  class DrawGround: public Anim
  {
    public:
      DrawGround( dirt* p )
      {
        m_dirt = p;
      }

      void animate( const float& t, AnimData *d );
      float controlDuration() const
      { return 0; }
      float totalDuration() const
      { return 1; }
    private:
      dirt* m_dirt;

  };

  class DrawAnim: public Anim
  {
    public:
      DrawAnim( plant* p )
      {
        m_plant = p;
      }

      void animate( const float& t, AnimData *d );
      float controlDuration() const
      { return 0; }
      float totalDuration() const
      { return 0; }
    private:
      plant* m_plant;
  };

} // visualizer

#endif // ANIMATIONS_H
