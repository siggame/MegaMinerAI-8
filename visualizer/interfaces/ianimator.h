#ifndef IANIMATOR_H
#define IANIMATOR_H

#include "common.h"

namespace visualizer
{

  struct AnimData
  {
  }; // AnimData
 
  struct Anim
  {
    virtual float controlDuration() const = 0;
    virtual float totalDuration() const = 0;
    float startTime; 
    float endTime;

    virtual void animate( const float& t, AnimData *d ) = 0;
  }; // Anim

#if 0
  struct IAnimator
  {
    virtual void addKeyFrame( const SmartPointer<Anim>& a ) = 0;
    virtual void addSubFrame( const size_t& keyFrame, const SmartPointer<Anim>& a ) = 0;

    virtual const size_t& numKeyFrames() = 0;

    class Iiterator
    {
      public:
        virtual void operator ++ ( int ) = 0;
        virtual SmartPointer<Anim> operator -> () = 0;
        virtual bool done() = 0;

    }; // iterator

    virtual SmartPointer<Iiterator> begin() = 0;
    virtual SmartPointer<Iiterator> end() = 0;

  }; // IAnimator
#endif
 
} // visualizer

#endif // IANIMATOR_H
