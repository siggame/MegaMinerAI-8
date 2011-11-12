#ifndef BEANSTALKER_H
#define BEANSTALKER_H

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>
#include <string>

using namespace std;

namespace visualizer
{

  class BeanStalker: public QObject
  {
    Q_OBJECT
    public:
      BeanStalker( const string& host, const int& port );

      void displayError( QAbstractSocket::SocketError S );

      string reserve();

      string sendCommand( string cmd );

    private:
      void cmdSend( string cmd );
      string pullWord();
      string pullLine();
      QTcpSocket* s;

  };

} // visualizer

#endif // BEANSTALKER_H
