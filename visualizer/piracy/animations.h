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
      const float& controlDuration() const;
      const float& totalDuration() const;
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
    public:
      void animate( float t, AnimData *d );
  };

  class DrawStack: public Anim
  {
    public:
      DrawStack( Stack *s )
      {
        m_stack = s;
      }
      void animate( float t, AnimData *d );
      const float& controlDuration() const;
      const float& totalDuration() const;
      Stack *m_stack;

  };

} // visualizer

#endif
