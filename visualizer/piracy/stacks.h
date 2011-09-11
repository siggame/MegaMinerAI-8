#ifndef STACKS_H
#define STACKS_H

#include <iostream>
#include <vector>
#include <map>
#include <list>
//#include "../interfaces/ianimationengine.h"
#include "frame.h"
using namespace std;

namespace visualizer
{
  // Ok here's what I'm thinking.
  // We use a map to categorize where units go in a stack
  // We actually store the stacks in a list for easy iterating
  // The map will point to the list where the unit should go.
  // If we need even more of a speed increase we use a 2D array
  // which will point to the maps which will point the lists. 
  // When rendering, the only thing that will/should exist is the list.
  // The maps would no longer be needed, and, as a result, neither
  // would the 2d array.

  template<class key, class stackType, class compare = less<key> >
  class StackOrganizer
  {
  public:
    StackOrganizer( IRenderer *renderer = 0 )
    {
      m_renderer = renderer;
    }
    ~StackOrganizer()
    {
  //    cout << "Destroy" << endl;
    }
    // Get stack will search for the existing stack
    // or create a new one if necessary
    stackType& getStack( const key& index );

    Frame& returnStackList();

  private:
    // This represents the map which will point to a particular point in the 
    // list
    std::map<key, SmartPointer<Animatable>, compare > m_stackMap;
    // This represents all the stacks that are present in the current frame.
    // We had to change to list instead of vector because when the vector
    // resizes, the pointers in m_stackMap became invalid because each element
    // in the vector had a new pointer.  

    Frame m_frame;
    IRenderer *m_renderer;

  };
   
}

#include "stacks.hpp"

#endif
