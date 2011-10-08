#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include "viruses.h"
#include "irenderer.h"

namespace visualizer
{

  class StartAnim: public Anim
  {
    public:
      void animate( const float& t, AnimData *d );

      float controlDuration() const
      { return 0; }
      float totalDuraion() const
      { return 1; }

  }; // StartAnim

  class DrawVirus: public Anim
  {
    public:
      DrawVirus( virus* v )
      {
        m_virus = v;
      } // DrawVirus()
      
      void animate( const float& t, AnimData* d );

      float controlDuration() const
      { return 0; }

      float totalDuration() const
      { return 0; }
    private:
      virus* m_virus;

  }; // DrawVirus

} // visualizer



#endif // ANIMATIONS_H
