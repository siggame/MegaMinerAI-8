#include "frame.h"

namespace visualizer
{
  void Frame::addAnimatable( const SmartPointer<Animatable>& animatable )
  {
    m_frame.push_back( animatable );
  }

  void Frame::addAnimatableFront( const SmartPointer<Animatable>& animatable )
  {
    m_frame.push_front( animatable );
  }

  std::list<SmartPointer<Animatable> >& Frame::getAnimations()
  {
    // @TODO Remove me
    //cout <<"Anims" << endl;
    //cout << (*m_frame.begin())->numKeyFrames() << endl;
    return m_frame;
  }

  const size_t Frame::size() const
  {
    return m_frame.size();
  }

} // visualizer
