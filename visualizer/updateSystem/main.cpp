#include <QApplication>
#include <QThread>
#include <QSharedMemory>
#include <QProcess>
#include <string>
#include <iostream>

#include "updatemonitor.h"

using namespace std;

using namespace SIGGAME_UPDATE;

int main( int argc, char *argv[] )
{

  QApplication app (argc, argv, false);

  UpdateMonitor *updater = new UpdateMonitor( "r99acm.device.mst.edu", &app );
  updater->setRemoteDirectory( "./visualizer" );
  updater->setLocalDirectory( "./" );
  updater->setMonitorInterval( 500000 );
  updater->checkForUpdate();
  updater->startMonitoring();

  QProcess *binary = new QProcess( &app );
  // visualizer for linux
  // visualizer.exe for windows
  binary->start( "../visualizer" );
  binary->waitForFinished();

  app.exec();

}
