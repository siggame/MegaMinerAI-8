#ifndef COMMON_H
#define COMMON_H

#include "exception.h"

#if __DEBUG__

#include <iostream>
#define SETUP(x) std::cout << x << " initialized at line " << __LINE__ << "." << endl;
#define THROW( x, y ) throw x( y, __FILE__, __LINE__ )

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
#endif
