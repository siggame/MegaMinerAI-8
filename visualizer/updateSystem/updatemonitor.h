#ifndef UPDATEMONITOR_H
#define UPDATEMONITOR_H 
#include <QFtp>
#include <QTimer>
#include "updatemonitor_exceptions.h"

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

  const MonitorStatus& status() const;

public:
  // Getters/Setters
  void setHostname( const QString& host );
  const QString& getHostname() const;

  void setRemoteDirectory( const QString& dir );
  const QString& getRemoteDirectory() const;

  void setLocalDirectory( const QString& dir );
  const QString& getLocalDirectory() const;

  void setMonitorInterval( const int& msec ); 
  const int& getMonitorInterval() const;

public slots:
  void commandDone( int id, bool error );
  void commandStart( int id );
  void stateChange( int state );
  void listUpdate( const QUrlInfo &i );

  void checkForUpdate();

private:
  QString m_hostName;
  QString m_remoteDir;
  QString m_localDir;
  QFtp::State m_ftpState;
  MonitorStatus m_monitorStatus; 

  QTimer *m_monitorTimer;
  int m_monitorTimeout;

  enum GenericStatus
  {
    S_None = 0,
    S_Waiting,
    S_Delivered
  };

  GenericStatus m_ftpStatus;
  GenericStatus m_timeStampStatus;

};


} // End of SIGGAME_UPDATE namespace

#endif
