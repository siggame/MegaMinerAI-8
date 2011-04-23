#include "updatemonitor.h"
#include <iostream>
#include <list>

using namespace std;

UpdateMonitor::UpdateMonitor( const QString& host, QObject* parent ) : QFtp( parent )
{
  m_host = host;
  connect( this, SIGNAL(commandFinished(int,bool)), this, SLOT(commandDone(int,bool)) );
  connect( this, SIGNAL(commandStarted(int)), this, SLOT( commandStart( int ) ) );
  connect( this, SIGNAL(stateChanged(int)), this, SLOT( stateChange( int ) ) );
  connect( this, SIGNAL(listInfo(const QUrlInfo&)), this, SLOT(listUpdate(const QUrlInfo&)));

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

void UpdateMonitor::setRemoteDirectory( const QString& dir )
{
  m_remoteDir = dir;
}

const QString& UpdateMonitor::getRemoteDirectory() const 
{
  return m_remoteDir;
}


