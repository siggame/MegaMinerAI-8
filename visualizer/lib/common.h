#ifndef COMMON_H
#define COMMON_H

#include "exception.h"

#if __DEBUG__

#include <stdio.h>
#include <iostream>

#endif

namespace visualizer 
{

#if __DEBUG__
#define SETUP(x) std::cout << x << " initialized at line " << __LINE__ << "." << endl;
#define THROW( x, y, ... ) \
  { \
  char message[512]; \
  sprintf( message, y, ##__VA_ARGS__ ); \
  throw x( message, __FILE__, __LINE__ ); \
  } 

#else

#define SETUP(x)
#define THROW( x, y )

#endif                           /* __DEBUG__ */

class Module
{
  public:
    static void setup();
    static void destroy();
};

} // visualizer

#endif
