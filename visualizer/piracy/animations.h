#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include <string.h>
#include "../interfaces/ianimationengine.h"
#include "piracy.h"
#include "stacks.h"
#include "piratemap.h"

namespace visualizer
{
  // For this to work properly, these need to have some 
  // sort of sandbox to play in. 
  // Possible idea is passing the original object which is a superclass
  // of some animation object
  // and passing a temp variable that we also declare that we pass to 
  // each class 

  // Ok, we're passing a storage structure each frame, but we need a way
  // to initialize it properly 
  class StartAnim: public Anim
  {
    public:
      StartAnim( Stack* s )
      {
        m_stack = s;
      }
      void animate( const float& t, AnimData *d );
      float controlDuration() const
      { return 0; }
      float totalDuration() const
      { return 0; }
    private:
      Stack *m_stack;

  };

  class LeftAnim: public Anim
  {
    public:
      void animate( const float& t, AnimData *d );

      float controlDuration() const
      { return 1; }
      float totalDuration() const
      { return 1; }
   
  };

  class RightAnim: public Anim
  {
    public: 
      void animate( const float& t, AnimData *d );

      float controlDuration() const
      { return 1; }
      float totalDuration() const
      { return 1; }
   
  };

  class UpAnim: public Anim
  {
    public:
      void animate( const float& t, AnimData *d );

      float controlDuration() const
      { return 1; }
      float totalDuration() const
      { return 1; }
   
  };

  class DownAnim: public Anim
  {
    public: 
      void animate( const float& t, AnimData *d );

      float controlDuration() const
      { return 1; }
      float totalDuration() const
      { return 1; }
   
  };

  class AttackAnim: public Anim
  {
    public:
      AttackAnim( const float& x, const float& y, Stack *s )
      {
        m_targetX = x;
        m_targetY = y;
        m_stack = s;
      }
      void animate( const float& t, AnimData *d );

      float controlDuration() const
      { return 0.1; }
      float totalDuration() const
      { return 1; }
   
    private:
      float m_targetX;
      float m_targetY;
      Stack *m_stack;
  };

  class TalkAnim: public Anim
  {
    private:
      string m_msg;
    public:
      TalkAnim( const char* msg )
      {
        m_msg = msg;
      }
      void animate( const float& t, AnimData *d );

      float controlDuration() const
      { return 0.0f; }

      float totalDuration() const
      { return 0.4f; }

  };

  class DrawStack: public Anim
  {
    public:
      DrawStack( Stack *s )
      {
        m_stack = s;
      }

    private:
      void animate( const float& t, AnimData *d );

      float controlDuration() const
      { return 0.0f; }

// Total Duration is 0 because it doesn't affect the animation lengths in anyway.  
      float totalDuration() const
      { return 0.0f; }

      Stack *m_stack;
  };

  class DrawMap: public Anim
  {
    public:
      DrawMap( PirateMap *m )
      {
        m_map = m;
      }

      void animate( const float& t, AnimData *d );
      float controlDuration() const
      { return 0.0f; }
      float totalDuration() const
      { return 0.0f; }

      PirateMap *m_map;
  };

} // visualizer

#endif
