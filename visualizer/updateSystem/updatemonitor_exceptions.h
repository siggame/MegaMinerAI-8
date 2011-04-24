#ifndef UPDATEMONITOR_EXCEPTIONS_H
#define UPDATEMONITOR_EXCEPTIONS_H

#include <iostream>
using namespace std;
#include <QString>

namespace SIGGAME_UPDATE
{
class Exception
{
public:
  Exception( const QString& exception );
};

class MonitorException
{
public:
  MonitorException( const QString& exception )
  {
    cerr << qPrintable( exception ) << endl;
  }
};

} // END OF SIGGAME_UPDATE namespace

#endif 
