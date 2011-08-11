#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "ianimationengine.h"

namespace visualizer
{
  struct Animator: public IAnimator
  {
    void addKeyFrame( const SmartPointer<Anim>& a );
    void addSubFrame( const size_t& keyFrame, const SmartPointer<Anim>& a );

    const size_t& numKeyFrames();

    class iterator: public Iiterator
    {
      public:
        iterator
          ( 
            std::list< pair<SmartPointer<Anim>, std::list<SmartPointer<Anim> > > >::iterator i,
            std::list< pair<SmartPointer<Anim>, std::list<SmartPointer<Anim> > > >::iterator end 
          );
        void operator ++ ( int );
        SmartPointer<Anim> operator -> ();
        bool done();
      private:
        std::list< pair<SmartPointer<Anim>, std::list<SmartPointer<Anim> > > >::iterator m_iter;
        std::list< pair<SmartPointer<Anim>, std::list<SmartPointer<Anim> > > >::iterator m_end;
        std::list< SmartPointer<Anim> >::iterator m_subIter;
        bool m_keyFrame;
        bool m_done;
    };

    SmartPointer<Iiterator> begin();
    SmartPointer<Iiterator> end();

    std::list< pair<SmartPointer<Anim>, std::list<SmartPointer<Anim> > >  > m_animList;
  }; // Animator 

} // visualizer

#endif
