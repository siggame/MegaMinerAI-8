#include "../piracy/stacks.h"

using namespace visualizer;

int main()
{

  for( int k = 0; k < 1000; k++ )
  {
    StackOrganizer< int, int > so;
    for( int i = 0; i < 1000; i++ )
    {
      so.getStack( i%10 ) = i;
    }
#if 1
    for( int i = 0; i < 1000; i++ )
    {
      so.getStack( i ) = 0;
    }

    for( int i = 0; i < 1000; i++ )
    {
      so.getStack( i ) = 2;/// += 1;
    }
#endif
  }


};
