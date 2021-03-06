#include "updatemonitor.h"
#include <iostream>
#include <list>

using namespace std;

namespace SIGGAME_UPDATE
{

UpdateMonitor::UpdateMonitor( const QString& host, QObject* parent ) : QFtp( parent )
{
  m_hostName = host;
  connectToHost( m_hostName );
  connect( this, SIGNAL(commandFinished(int,bool)), this, SLOT(commandDone(int,bool)) );
  connect( this, SIGNAL(commandStarted(int)), this, SLOT( commandStart( int ) ) );
  connect( this, SIGNAL(stateChanged(int)), this, SLOT( stateChange( int ) ) );
  connect( this, SIGNAL(listInfo(const QUrlInfo&)), this, SLOT(listUpdate(const QUrlInfo&)));

  m_monitorTimer = new QTimer( this );
  connect( m_monitorTimer, SIGNAL(timeout()), this, SLOT(checkForUpdate()) );
  m_monitorTimeout = 500000;

  m_ftpStatus = S_None;
  m_timeStampStatus = S_None;

}


void UpdateMonitor::startMonitoring()
{
  if( m_monitorStatus == Monitoring )
    throw MonitorException( "Already Monitoring FTP" );

  m_monitorStatus = Monitoring;
  m_monitorTimer->start( m_monitorTimeout );

}

void UpdateMonitor::stopMonitoring()
{

  if( m_monitorStatus == Waiting )
    throw MonitorException( "Already Stopped" );

  m_monitorStatus = Waiting;
  m_monitorTimer->stop();
}

void UpdateMonitor::commandStart( int id )
{
  //cout << "Command Started: " << id << endl;
}

const UpdateMonitor::MonitorStatus& UpdateMonitor::status() const
{
  return m_monitorStatus;
}

void UpdateMonitor::commandDone( int id, bool error )
{

  //cout << "Command Finished: " << id << ", Error: " << error << endl;
}

void UpdateMonitor::stateChange( int state )
{
  m_ftpState = (QFtp::State)state;
  if( m_ftpStatus == Waiting && m_ftpState == QFtp::LoggedIn )
  {
    m_ftpStatus = S_Delivered;
    checkForUpdate();
  }
}

void UpdateMonitor::listUpdate( const QUrlInfo& i )
{
  if( i.name() == QString( "update.lst" ) )
  {
    cout << qPrintable( i.name() + QString( " Time: " ) + i.lastModified().toString( "dd.MM.yyyy:hh:mm:ss.zzz" ) ) << endl;

    m_timeStampStatus = S_Delivered;
    checkForUpdate();
  }
}

void UpdateMonitor::checkForUpdate()
{
  if( m_ftpState != QFtp::LoggedIn ) 
  {
    m_ftpStatus = S_Waiting;
    login();
    return;
  }

  if( m_ftpStatus == S_Delivered )
  {
    m_ftpStatus = S_None;
  }

  if( m_timeStampStatus == S_None )
  {
    list( m_remoteDir );
    m_timeStampStatus = S_Waiting;
    return;
  } else if( m_timeStampStatus == S_Delivered )
  {
    m_timeStampStatus = S_None;
  } else 
  {
    throw MonitorException( "No Timestamp Achieved Before Next Call" );
  }




}

///  Getters and Setters Below Here


void UpdateMonitor::setHostname( const QString& host )
{
  // TODO: Check if this is different from our current host
  //  and if so, disconnect from the current one
  m_hostName = host;

}

const QString& UpdateMonitor::getHostname() const
{
  return m_hostName;
}

void UpdateMonitor::setRemoteDirectory( const QString& dir )
{
  m_remoteDir = dir;
}

const QString& UpdateMonitor::getRemoteDirectory() const 
{
  return m_remoteDir;
}

void UpdateMonitor::setLocalDirectory( const QString& dir )
{
  m_localDir = dir;
}

const QString& UpdateMonitor::getLocalDirectory() const
{
  return m_localDir;
}

void UpdateMonitor::setMonitorInterval( const int& msec ) 
{
  m_monitorTimeout = msec;
}

} // END OF SIGGAME_UPDATE namespace
