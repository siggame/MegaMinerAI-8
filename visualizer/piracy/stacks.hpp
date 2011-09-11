#include "stacks.h"

namespace visualizer
{

  template<class key, class stackType, class compare>
  stackType& StackOrganizer<key, stackType, compare>::getStack( const key& index )
  {
    stackType *p;
    typename
    std::map<key, SmartPointer<Animatable>, compare>::iterator i = m_stackMap.find( index );
    if( i != m_stackMap.end() )
    {
      // Already exists.  What are the chances?!
      p = (stackType*)(&*i->second);
    }
    else
    {
      //m_stacks.push_back( new stackType() );
      p = new stackType( m_renderer );
      SmartPointer<Animatable> s_p( p );
      m_frame.addAnimatable( s_p );
      // Return pointer to last element in list
      m_stackMap[ index ] = s_p; // = (stackType*)&*m_stacks.back();
    }

    return *p;

  }

  template<class key, class stackType, class compare>
  Frame& StackOrganizer<key, stackType, compare>::returnStackList() 
  {
    return m_frame;
  }

}
