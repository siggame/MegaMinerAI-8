#ifndef FRAMECONTAINER_H
#define FRAMECONTAINER_H

namespace visualizer
{
  
  class FrameContainer: public IFrameContainer
  {
  public:
    void addFrame( std::list<SmartPointer<Animatable> >& frame );

  private:
     // We're going to want to put this in a dedicated class so we can allow a mutex
    // to automatically lock and unlock around it.
    std::vector<std::list<SmartPointer<Animatable> > >* m_frames;

  };

} // visualizer


#endif
