#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>
#include <string>
using namespace std;

namespace visualizer
{

class Exception
{
  public:
    Exception( std::string e, std::string fileName, unsigned int lineNum )
    {
      cerr << endl;
      cerr << "============= General Exception ============= " << endl;
      cerr << " Error: " << e << endl;
      cerr << " File:  " << fileName << ":" << lineNum << endl;
      cerr << endl;
    }
};

} // visualizer

#endif
