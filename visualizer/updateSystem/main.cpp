#include <QApplication>
#include <QThread>
#include <QSharedMemory>
#include <QProcess>
#include <string>
#include <iostream>

#include "ftp.h"

using namespace std;
int main( int argc, char *argv[] )
{

  QApplication app (argc, argv, false);

  UpdateMonitor *ftp = new UpdateMonitor( "r99acm.device.mst.edu", &app );
  ftp->setRemoteDirectory( "/visualizer" );

  cout << "Connecting?" << endl;

  app.exec();

}
