#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>
#include <string>

#ifdef __GNUC__
#include <execinfo.h>
#define __STACKTRACE__
#endif

using namespace std;

namespace visualizer
{

class Exception
{
  public:
    Exception( std::string e, std::string fileName, unsigned int lineNum )
    {
      cerr << endl;
      cerr << "=================== General Exception =================== " << endl;
      cerr << " Error: " << e << endl;
      cerr << " File:  " << fileName << ":" << lineNum << endl;
#ifdef __STACKTRACE__ 
      // Exception is closing everything down anyway.  May as well use up some memory
      void *array[256];
      size_t size;
      cerr << " Stack Trace: " << endl;
      size = backtrace( array, 10 );
      backtrace_symbols_fd( array, size, 2 );

#endif
      cerr << endl;
    }

};

} // visualizer

#endif
