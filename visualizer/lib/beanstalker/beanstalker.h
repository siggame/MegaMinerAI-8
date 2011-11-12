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


      const string& lastJob() const
      {
        return m_lastJob;
      }

    private:
      void cmdSend( string cmd );
      string pullWord();
      string pullLine();
      QTcpSocket* s;

      string m_lastJob;

  };

} // visualizer

#endif // BEANSTALKER_H
