#include "stacks.h"

namespace visualizer
{

  template<class key, class stackType, class compare>
  stackType& StackOrganizer<key, stackType, compare>::getStack( key& index )
  {
    stackType *p;
    typename
    std::map<key, stackType*, compare>::iterator i = m_stackMap.find( index );
    if( i != m_stackMap.end() )
    {
      // Already exists.  What are the chances?!
      p = i->second;
    }
    else
    {
      m_stacks.push_back( stackType() );
      m_stackMap[ index ] = p = &(*(m_stacks.end()-1));

    }

    return *p;

  }


}
