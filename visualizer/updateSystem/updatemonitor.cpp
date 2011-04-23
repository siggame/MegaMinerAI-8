#include "updatemonitor.h"
#include <iostream>
#include <list>

using namespace std;

namespace SIGGAME_UPDATE
{

UpdateMonitor::UpdateMonitor( const QString& host, QObject* parent ) : QFtp( parent )
{
  m_hostName = host;
  connect( this, SIGNAL(commandFinished(int,bool)), this, SLOT(commandDone(int,bool)) );
  connect( this, SIGNAL(commandStarted(int)), this, SLOT( commandStart( int ) ) );
  connect( this, SIGNAL(stateChanged(int)), this, SLOT( stateChange( int ) ) );
  connect( this, SIGNAL(listInfo(const QUrlInfo&)), this, SLOT(listUpdate(const QUrlInfo&)));

}


void UpdateMonitor::startMonitoring()
{
  if( m_monitorStatus == Monitoring )
    throw MonitorException( "Already Monitoring FTP" );

  m_monitorStatus = Monitoring;

}

void UpdateMonitor::stopMonitoring()
{

  if( m_monitorStatus == Waiting )
    throw MonitorException( "Already Stopped" );

  m_monitorStatus = Waiting;
}

void UpdateMonitor::commandStart( int id )
{
  cout << "Command Started: " << id << endl;
}

void UpdateMonitor::commandDone( int id, bool error )
{

  cout << "Command Finished: " << id << ", Error: " << error << endl;
}

void UpdateMonitor::stateChange( int state )
{
  currentState = (QFtp::State)state;
}

void UpdateMonitor::listUpdate( const QUrlInfo& i )
{
  if( i.name() == QString( "visualizer.exe" ) )
  {
    cout << qPrintable( i.lastModified().toString( "dd.MM.yyyy:hh:mm:ss.zzz" ) ) << endl;
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

} // END OF SIGGAME_UPDATE namespace
