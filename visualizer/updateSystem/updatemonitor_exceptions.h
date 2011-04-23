#ifndef UPDATEMONITOR_EXCEPTIONS_H
#define UPDATEMONITOR_EXCEPTIONS_H

#include <QString>

namespace SIGGAME_UPDATE
{
  class Exception
  {
    Exception( const QString& exception );
  };

  class MonitorException
  {
    MonitorException( const QString& exception )
    {
      cerr << qPrintable( exception ) << endl;
    }
  };

} // END OF SIGGAME_UPDATE namespace

#endif 
