#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include <string.h>
#include "../interfaces/ianimationengine.h"
#include "piracyStack.h"
#include "stacks.h"

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
      void animate( float t, AnimData *d );
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
      void animate( float t, AnimData *d );
   
  };

  class RightAnim: public Anim
  {
    public: 
      void animate( float t, AnimData *d );
  };

  class UpAnim: public Anim
  {
    public:
      void animate( float t, AnimData *d );
  };

  class DownAnim: public Anim
  {
    public: 
      void animate( float t, AnimData *d );
  };

  class AttackAnim: public Anim
  {
    public:
      void animate( float t, AnimData *d );
    private:
      float m_targetX;
      float m_targetY;
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
      void animate( float t, AnimData *d );

      float controlDuration() const
      { return 0.0f; }

      float totalDuration() const
      { return 0.4f; }

  };

  class DrawStack: public Anim
  {
    public:
      DrawStack()
      {
        THROW( Exception, "Must pass a stack pointer to the constructor." );
      }


      DrawStack( Stack *s )
      {
        m_stack = s;
      }

    private:
      void animate( float t, AnimData *d )
      {
      }

      float controlDuration() const
      { return 0.2f; }

      float totalDuration() const
      { return 0.2f; }

      Stack *m_stack;

  };

} // visualizer

#endif
