#ifndef COMMON_H
#define COMMON_H

#if __DEBUG__

#include <iostream>
#define SETUP(x) std::cout << x << " initialized at line " << __LINE__ << "." << endl;

#else

#define SETUP(x)


#endif /* __DEBUG__ */

class Module
{
public:
  static void setup();
  static void destroy();
};


#endif
