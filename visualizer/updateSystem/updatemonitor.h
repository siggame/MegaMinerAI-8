#ifndef FTP_H
#define FTP_H
#include <QFtp>


class UpdateMonitor: public QFtp
{
  Q_OBJECT
public:
  UpdateMonitor( const QString& host, QObject* parent = 0 );

  void host( const QString& host )
  {
    m_host = host;
  }

  const QString& host()
  {
    return m_host;
  }

  void setRemoteDirectory( const QString& dir );
  const QString& getRemoteDirectory() const;



public slots:
  void commandDone( int id, bool error );
  void commandStart( int id );
  void stateChange( int state );
  void listUpdate( const QUrlInfo &i );

private:
  QString m_host;
  QString m_file;
  QString m_remoteDir;
  QFtp::State currentState;


};



#endif
