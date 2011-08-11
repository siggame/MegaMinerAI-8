#ifndef IANIMATOR_H
#define IANIMATOR_H

#include "common.h"

namespace visualizer
{
  struct Anim
  {
    virtual float controlDuration() const = 0;
    virtual float totalDuration() const = 0;
    float startTime; 
    float endTime;
  }; // Anim

  struct IAnimator
  {
    virtual void addKeyFrame( const SmartPointer<Anim>& a ) = 0;
    virtual void addSubFrame( const size_t& keyFrame, const SmartPointer<Anim>& a ) = 0;

    virtual const size_t& numKeyFrames() = 0;

  }; // IAnimator
 
  struct AnimData
  {
  }; // AnimData
 
} // visualizer

#endif // IANIMATOR_H
