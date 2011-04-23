#ifndef UPDATEMONITOR_H
#define UPDATEMONITOR_H 
#include <QFtp>
#include <QTimer>

namespace SIGGAME_UPDATE
{

class UpdateMonitor: public QFtp
{
  Q_OBJECT
public:
  UpdateMonitor( const QString& host, QObject* parent = 0 );

  void startMonitoring();
  void stopMonitoring();

  enum MonitorStatus
  {
    Monitoring = 0,
    Waiting
  };

  void status();

public:
  // Getters/Setters
  void setHostname( const QString& host );
  const QString& getHostname() const;

  void setRemoteDirectory( const QString& dir );
  const QString& getRemoteDirectory() const;

  void setLocalDirectory( const QString& dir );
  const QString& getLocalDirectory() const;

public slots:
  void commandDone( int id, bool error );
  void commandStart( int id );
  void stateChange( int state );
  void listUpdate( const QUrlInfo &i );

private:
  QString m_hostName;
  QString m_remoteDir;
  QString m_localDir;
  QFtp::State currentState;
  MonitorStatus m_monitorStatus; 


};


} // End of SIGGAME_UPDATE namespace

#endif
