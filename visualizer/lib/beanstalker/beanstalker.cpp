#include "beanstalker.h"
#include "common.h"

namespace visualizer
{
  BeanStalker::BeanStalker( const string& host, const int& port )
  {
    s = new QTcpSocket( this );

    s->connectToHost( host.c_str(), port );

    if( !s->waitForConnected( 5000 ) )
    {
      WARNING
        (
        "Could not connect to %s", host.c_str()
        );
        return;
    }

    // We're connected

  }

  void BeanStalker::displayError( QAbstractSocket::SocketError s )
  {
    WARNING
      (
      "Socket Error QTcpSocket: %d", s 
      );
  }

  string BeanStalker::pullWord()
  {
    string word = "";
    QDataStream inout( s );
    char letter;

    do
    {
      while( !s->bytesAvailable() )
      {
        if( !s->waitForReadyRead() )
        {
          WARNING
            (
            "Could not reserve your glog log." 
            );
        }
      }

      inout.readRawData( &letter, 1 );

      word += letter;

    } while( letter != ' ' && letter != '\r' );

    if( letter == '\r' )
      inout.readRawData( &letter, 1 );

    word.erase( word.size()-1, 1 );

    return word;

  }

  string BeanStalker::pullLine()
  {
    string line = "";
    QDataStream inout( s );
    char letter;

    do
    {
      while( !s->bytesAvailable() )
      {
        if( s->waitForReadyRead() )
        {
          WARNING
            (
            "Could not reserve your glog log." 
            );
        }
      }

      inout.readRawData( &letter, 1 );

      line += letter;

    } while( letter != '\r' );

    if( letter == '\r' )
      inout.readRawData( &letter, 1 );

    line.erase( line.size()-1, 1 );

    return line;

  }

  string BeanStalker::reserve()
  {
    cmdSend( "reserve" );

    string response = pullWord();
    if( response.compare( "RESERVED" ) )
    {
      WARNING
        (
        "Could not get gamelog."
        );

      return "";

    }

    m_lastJob = pullWord();

    pullLine(); // discard rest of the line

    return pullLine();

  }

  void BeanStalker::cmdSend( string cmd )
  {
    cmd += "\r\n";

    QDataStream inout( s );
    inout.setVersion( QDataStream::Qt_4_0 );
    inout.writeRawData( cmd.c_str(), cmd.size() );

  }

  string BeanStalker::sendCommand( string cmd )
  {
    cmdSend( cmd );
    string ret = "NORESPONSE";

    if( s->waitForReadyRead() )
    {
      QDataStream inout( s );
      size_t readSize = s->bytesAvailable();
      char *buff = new char[ readSize ];
      inout.readRawData( buff, readSize );

      ret = buff;
      delete [] buff;

    }
    else
    {
      WARNING
        (
        "No response from the server." 
        );
    }

    return ret;

  }
  
} // visualizer
