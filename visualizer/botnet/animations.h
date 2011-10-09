#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include "viruses.h"
#include "irenderer.h"

namespace visualizer
{

  class StartAnim: public Anim
  {
    public:
      StartAnim() {}
      void animate( const float& t, AnimData *d );

      float controlDuration() const
      { return 0; }
      float totalDuration() const
      { return 0; }

  }; // StartAnim

  class Appear: public Anim
  {
    public:
      void animate( const float& t, AnimData *d );
      float controlDuration() const
      {
        return 0;
      }
      float totalDuration() const
      {
        return 1;
      }
  };

  class StartVirus: public Anim
  {
    public:
      StartVirus( virus* v )
      {
        m_virus = v;
      }

      void animate( const float& t, AnimData *d )
      {
        VirusData* v = (VirusData*)d;
        v->x = m_virus->x;
        v->y = m_virus->y;
      }

      float controlDuration() const
      { return 0; }
      float totalDuration() const
      { return 0; }

    private:
      virus* m_virus;
  };

  class LeftAnim: public Anim
  {
    public:
      void animate( const float& t, AnimData *d );

      float controlDuration() const
      { return 1; }
      float totalDuration() const
      { return 1; }

  }; // LeftAnim

  class RightAnim: public Anim
  {
    public:
      void animate( const float& t, AnimData *d );

      float controlDuration() const
      { return 1; }
      float totalDuration() const
      { return 1; }

  }; // RightAnim

  class UpAnim: public Anim
  {
    public:
    void animate( const float& t, AnimData *d );

    float controlDuration() const
    { return 1; }
    float totalDuration() const
    { return 1; }

  }; // UpAnim

  class DownAnim: public Anim
  {
    public:
    void animate( const float& t, AnimData *d );

    float controlDuration() const
    { return 1; }
    float totalDuration() const
    { return 1; }
  }; // DownAnim

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

  class DrawBase: public Anim
  {
    public:
      DrawBase( base* b )
      {
        m_base = b;
      }

      void animate( const float& t, AnimData* d );

      float controlDuration() const
      { return 0; }

      float totalDuration() const
      { return 0; }

    private:
      base* m_base;
  }; // DrawBase

  class DrawTile: public Anim
  {
    public: 
      DrawTile( tile* t )
      {
        m_tile = t;
      }

      void animate( const float& t, AnimData* d );

      float controlDuration() const
      { return 0; }

      float totalDuration() const
      { return 0; }

    private:
      tile* m_tile;
  }; // DrawTile

} // visualizer



#endif // ANIMATIONS_H
