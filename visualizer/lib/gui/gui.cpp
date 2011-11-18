#include "gui.h"
#include "../games/games.h"
#include "../renderer/renderer.h"
#include "../beanstalker/beanstalker.h"
#include <QDesktopServices>
#include <Qt>

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>

using namespace std;

namespace visualizer
{

  _GUI *GUI = 0;

  _GUI::~_GUI()
  {
    delete m_helpContents;
    delete m_centralWidget;
  }

  bool _GUI::setup()
  {
    if( !GUI )
    {
      GUI = new _GUI;
    } else
    {
      THROW( Exception, "GUI Already Setup" );
    }

    GUI->m_isSetup = GUI->doSetup();
    return GUI->m_isSetup;
  }


  bool _GUI::clear()
  {
    return true;
  }

  bool _GUI::create()
  {

    return true;
  }


  bool _GUI::destroy()
  {
    if( !clear() )
      return false;

    return true;
  }

  bool _GUI::isSetup()
  {
    return m_isSetup;
  }


  void _GUI::dragEnterEvent( QDragEnterEvent* evt )
  {
    // We may want to filter what's dropped on the window at some point
    evt->acceptProposedAction();
  }

  void _GUI::loadGamestring( char* log, const size_t& length )
  {
    bool parserFound = false;

    std::string fullLog;
    if( log[ 0 ] == 'B' && log[ 1 ] == 'Z' && ( log[ 2 ] == 'h' || log[ 2 ] == '0' ) )
    {
      const int megs = 25;
      unsigned int size = megs * 1024*1024;
      char *output = new char[ size-1 ];

      BZ2_bzBuffToBuffDecompress( output, &size, log, length, 0, 0 );
      output[ size ] = 0;
      fullLog = output;

      delete [] output;     
    }
    else
    {
      fullLog = log;
    }


    for
      ( 
      std::vector<IGame*>::iterator i = Games->gameList().begin(); 
      i != Games->gameList().end() && !parserFound;
      i++ 
      )
    {
      QRegExp rx( (*i)->logFileInfo().regex.c_str() );
      rx.setPatternSyntax( QRegExp::RegExp2 );
      
      if( rx.indexIn( fullLog.c_str() ) != -1 )
      {
        TimeManager->setTurn( 0 );
        (*i)->loadGamelog( fullLog );
        parserFound = true;
      }

    }

    if( !parserFound )
    {
      THROW( Exception, "An appropriate game player could not be found!" );
    }
  }

  void _GUI::loadGamelog( std::string gamelog )
  {
    ifstream file_gamelog( gamelog.c_str(), ifstream::in );
    if( file_gamelog.is_open() )
    {
      
      size_t length;
      file_gamelog.seekg( 0, ios::end );
      length = file_gamelog.tellg();
      file_gamelog.seekg( 0, ios::beg );

      char *input = new char[ length + 1 ];
      input[ length ] = 0;
      file_gamelog.read( input, length );

      file_gamelog.close();

      loadGamestring( input, length );

      delete [] input;
    }

  }


  void _GUI::update()
  {
    m_controlBar->update();
  }


  void _GUI::dropEvent( QDropEvent* evt )
  {
    const QMimeData* mimeData = evt->mimeData();
    
    if( mimeData->hasUrls() )
    {
      QStringList pathList;
      QList<QUrl> urlList = mimeData->urls();

      for( size_t i = 0; i < urlList.size() && i < 32; ++i )
      {
        pathList.append( urlList.at( i ).toLocalFile() );
      }

      string path = urlList.at( 0 ).toLocalFile().toAscii().constData();
      loadGamelog( path );


    }

  }


  void _GUI::appendConsole( string line )
  {
    QString param;
    param.append( line.c_str() );
    appendConsole( param );
  }


  void _GUI::appendConsole( QString line )
  {
    _GUI::m_consoleArea->append( line );
  }


  void _GUI::clearConsole()
  {

    _GUI::m_consoleArea->clear();
  }


  void _GUI::resizeEvent( QResizeEvent* evt )
  {
    if(!m_dockWidget->isFloating())//competitor hasn't torn off our dock window
    {
      int w = width();
      int h = height();

      if( h > w )
      {
        int temp = w;
        w = h;
        h = temp;
      }

      //m_dockWidget->resize( Singleton<_GUI>::width() - Renderer<DupObj>::height(), -1 );
      #if 1
      m_dockWidget->setMinimumWidth( w - h);
      m_dockWidget->hide();
      #endif
    }
    QMainWindow::resizeEvent( evt );
  }


  void _GUI::helpContents()
  {
    if( OptionsMan->exists( "helpURL" ) )
    {
      QDesktopServices::openUrl( QUrl( OptionsMan->getStr( "helpURL" ).c_str() ) );
    } else
    {
      QDesktopServices::openUrl( QUrl( "http://www.megaminerai.com" ) );
    }
  }


  void _GUI::fileOpen()
  {
    /* The following is almost entirely a dirty hack to persistently keep the
     * most recent directory to be default for the "Open Gamelog" dialog.
     * This works WONDERS for usability.
     */
    ifstream dirinfoIN;
    dirinfoIN.open("dirinfo.txt");
    if (dirinfoIN.is_open())
    {
      string line;
      while ( dirinfoIN.good() )
      {
        getline (dirinfoIN,line);
        m_previousDirectory.clear();
        m_previousDirectory.append(QString::fromStdString(line));
      }
      dirinfoIN.close();
    }

    QFileDialog fileDialog;

    QString filename = fileDialog.getOpenFileName(
      this,
      tr( "Open Gamelog" ),
      m_previousDirectory,
      tr( "Gamelogs (*.gamelog *.glog);;All Files (*.*)") ).toAscii().constData();

    if( filename.size() > 0 )
    {
      m_previousDirectory = filename;

      ofstream dirinfoOUT;
      dirinfoOUT.open("dirinfo.txt");
      dirinfoOUT << m_previousDirectory.toStdString();
      dirinfoOUT.close();
      loadGamelog( filename.toStdString() );
    }

  }

  void _GUI::closeEvent( QCloseEvent* event )
  {
    Renderer->destroy();
  }

  void _GUI::displayError( const QAbstractSocket::SocketError& err )
  {
    cout << err << endl;
  }

  bool _GUI::loadInProgress() const
  {
    return m_loadInProgress;
  }

  void _GUI::loadThatShit( bool err )
  {
    if( !err )
    {
      QByteArray arr = m_http->readAll();
      if( arr.size() == 0 )
        return;
      char *temp = new char[ arr.size() ];
      memcpy( temp, arr.constData(), arr.size() );
      loadGamestring( temp, arr.size() );
      m_loadInProgress = false;
      delete [] temp;
    }
  }

  void _GUI::requestGamelog()
  {
    BeanStalker b( "r09mannr4.device.mst.edu", 11300 );

    b.sendCommand( "watch visualizer-requests" );

    string glogPath = b.reserve();
    b.sendCommand( string( "delete ") + b.lastJob() );
    QUrl url( glogPath.c_str() );
    
    m_loadInProgress = true;

    m_http->setHost( url.host() );
    m_http->get( url.path() );
    

  }

  bool _GUI::doSetup()
  {

    m_loadInProgress = false;

    m_http = new QHttp( this );
    connect( m_http, SIGNAL( done( bool) ), this, SLOT( loadThatShit(bool) ) );

    connect( this, SIGNAL( close() ), this, SLOT( onClose() ) );

    setAcceptDrops( true );

    m_centralWidget = new CentralWidget( this );
    setCentralWidget( m_centralWidget );
    createActions();
    buildControlBar();

    setWindowIcon( QIcon( "icon.png" ) );

    createMenus();
    buildToolSet();

    // If we're in arenaMode, change some settings
    if(
      !OptionsMan->exists( "arenaMode" ) ||
      OptionsMan->getBool( "arenaMode" ) ||
      !OptionsMan->getStr( "gameMode" ).compare( "arena" )

      )
    {
      menuBar()->hide();
      setFullScreen(true);
      m_dockWidget->hide();
      requestGamelog();
    }

    //If we're in demonstrationMode, change different settings
    if(
      !OptionsMan->exists( "demonstrationMode" ) ||
      OptionsMan->getBool( "demonstrationMode" )
      )
    {
      menuBar()->hide();
      setFullScreen(true);
      m_dockWidget->hide();
    }

    setWindowState(
      windowState()
      | Qt::WindowActive
      | Qt::WindowMaximized
      );

    show();

    m_previousDirectory = QDir::homePath();

    return true;
  }

  void _GUI::newReadyConnect()
  {
#if 0
    QTcpSocket *client = m_visReadyServer->nextPendingConnection();

    QDataStream inout( (QIODevice*)client );
    inout.setVersion( QDataStream::Qt_4_0 );

    char rfg = TimeManager->readyForGamelog();

    inout.writeRawData( (char*)&rfg, 1 );

    client->disconnectFromHost();

#endif
  }

  void _GUI::newConnect()
  {
#if 0
    QTcpSocket *client = m_server->nextPendingConnection();

    QDataStream inout( (QIODevice*)client );
    inout.setVersion( QDataStream::Qt_4_0 );

    unsigned int fileSize = 20;


    while( (unsigned int)client->bytesAvailable() < sizeof( fileSize ) )
    {
      if( !client->waitForReadyRead( 5000 ) )
      {
        THROW
          (
          Exception,
          "Didn't get that gamelog in time."
          );
      }
    }

    inout >> fileSize;

    while( (unsigned int)client->bytesAvailable() < fileSize )
    {
      if( !client->waitForReadyRead( 5000 ) )
      {
        THROW
          (
          Exception,
          "Didn't get that gamelog in time."
          );
      }
    }

    char *gamelog = new char[ fileSize + 1 ];
    inout.readRawData( gamelog, fileSize );
    gamelog[ fileSize ] = 0;

    loadGamestring( gamelog, fileSize );

    delete [] gamelog;

    client->disconnectFromHost();
#endif

  }

  void _GUI::buildControlBar()
  {
    m_statusBar = statusBar();
    m_statusBar -> setMaximumHeight(20);
    m_controlBar = new ControlBar( this );

    m_statusBar->addPermanentWidget( m_controlBar, 100 );

  }


  void _GUI::createActions()
  {
    m_helpContents = new QAction( tr( "&Contents" ), this );
    m_helpContents->setShortcut( tr( "F1" ) );
    m_helpContents->setStatusTip(
      tr( "Open Online Help For This Game" )
      );
    connect( m_helpContents, SIGNAL(triggered()), this, SLOT(helpContents()) );

    m_fileOpen = new QAction( tr( "&Open" ), this );
    m_fileOpen->setShortcut( tr( "Ctrl+O" ) );
    m_fileOpen->setStatusTip(
      tr( "Open A Gamelog" )
      );
    connect( m_fileOpen, SIGNAL(triggered()), this, SLOT(fileOpen()) );

    toggleFullScreenAct = new QAction( tr("&Full Screen"), this );
    toggleFullScreenAct->setShortcut( tr("F11" ) );
    toggleFullScreenAct->setStatusTip( tr("Toggle Fullscreen Mode") );
    connect( toggleFullScreenAct, SIGNAL(triggered()), this, SLOT(toggleFullScreen()) );

    m_fileExit = new QAction( tr( "&Quit" ), this );
    m_fileExit->setShortcut( tr( "Ctrl+Q" ) );
    m_fileExit->setStatusTip(
      tr( "Close the Visualizer" )
      );
    connect( m_fileExit, SIGNAL(triggered()), this, SLOT(close()) );

    (void) new QShortcut( QKeySequence( tr( "Space" ) ), this, SLOT( togglePlayPause() ) );
    (void) new QShortcut( QKeySequence( tr( "Ctrl+F" ) ), this, SLOT( fastForwardShortcut() ) );
    (void) new QShortcut( QKeySequence( tr( "Ctrl+R" ) ), this, SLOT( rewindShortcut() ) );
    (void) new QShortcut( QKeySequence( tr( "Right" ) ), this, SLOT( stepTurnForwardShortcut() ) );
    (void) new QShortcut( QKeySequence( tr( "Left" ) ), this, SLOT( stepTurnBackShortcut() ) );
    (void) new QShortcut( QKeySequence( tr("Escape") ), this, SLOT( catchEscapeKey() ) );

    //Ugly hack
    (void) new QShortcut( QKeySequence( Qt::Key_1 ), this, SLOT( turnPercentageShortcut1() ) );
    (void) new QShortcut( QKeySequence( Qt::Key_2 ), this, SLOT( turnPercentageShortcut2() ) );
    (void) new QShortcut( QKeySequence( Qt::Key_3 ), this, SLOT( turnPercentageShortcut3() ) );
    (void) new QShortcut( QKeySequence( Qt::Key_4 ), this, SLOT( turnPercentageShortcut4() ) );
    (void) new QShortcut( QKeySequence( Qt::Key_5 ), this, SLOT( turnPercentageShortcut5() ) );
    (void) new QShortcut( QKeySequence( Qt::Key_6 ), this, SLOT( turnPercentageShortcut6() ) );
    (void) new QShortcut( QKeySequence( Qt::Key_7 ), this, SLOT( turnPercentageShortcut7() ) );
    (void) new QShortcut( QKeySequence( Qt::Key_8 ), this, SLOT( turnPercentageShortcut8() ) );
    (void) new QShortcut( QKeySequence( Qt::Key_9 ), this, SLOT( turnPercentageShortcut9() ) );
    (void) new QShortcut( QKeySequence( Qt::Key_0 ), this, SLOT( turnPercentageShortcut0() ) );
  }


  void _GUI::createMenus()
  {
    QMenu *menu;
    menu = menuBar()->addMenu( tr( "&File" ) );
    menu->addAction( m_fileOpen );
    menu->addSeparator();
    menu->addAction( m_fileExit );

    menu = menuBar()->addMenu( tr( "&Edit" ) );

    menu = menuBar()->addMenu( tr( "&View" ) );
    menu->addAction(toggleFullScreenAct);

    menu = menuBar()->addMenu( tr( "&Help" ) );
    menu->addAction( m_helpContents );

  }


  void _GUI::buildToolSet()
  {
    // Create the dock
    m_dockWidget = new QDockWidget( this );
    // Give it a frame to hold a layout
    m_dockLayoutFrame = new QFrame( m_dockWidget );
    // Give this frame a layout
    m_dockLayout = new QVBoxLayout( m_dockLayoutFrame );
    // Console area to the left
    m_consoleArea = new QTextEdit( m_dockLayoutFrame );
    m_consoleArea -> setReadOnly(1);

    // Allow users to stupidly move this as small as they like
    m_dockWidget->setMinimumHeight( 0 );
    m_dockWidget->setMinimumWidth( 0 );

    // Add Buffer so we don't feel claustrophobic
    m_dockLayout->setContentsMargins( 2, 0, 2, 0 );

    // Add the console to the layout
    m_dockLayout->addWidget( m_consoleArea );

    // Add the frame to the actual dock
    m_dockWidget->setWidget( m_dockLayoutFrame );
    // Add the dock to the main window
    addDockWidget( Qt::RightDockWidgetArea, m_dockWidget );

  }


  void _GUI::closeGUI()
  {
    close();
  }


  void _GUI::toggleFullScreen()
  {
    setFullScreen(!fullScreen);
  }


  void _GUI::togglePlayPause()
  {
    m_controlBar->play();
  }


  void _GUI::fastForwardShortcut()
  {
    m_controlBar->fastForward();
  }


  void _GUI::rewindShortcut()
  {
    m_controlBar -> rewind();
  }


  void _GUI::turnPercentageCalc(int value)
  {
    float turnPercent = value /9.0;
    TimeManager->setTurn((int) floor(turnPercent * TimeManager->getNumTurns()));
  }


  void _GUI::stepTurnForwardShortcut()
  {
    TimeManager->setSpeed(0);
    if( TimeManager->getTurnPercent() != 1-0.99999f && TimeManager->getTurnPercent() != 0.99999f && TimeManager->getTurnPercent() != 0.99999f-0.5f )
    {
      TimeManager->setTurnPercent( 0.99999f );
    }

    TimeManager->setTurnPercent( TimeManager->getTurnPercent() + 0.5f );
  }


  void _GUI::stepTurnBackShortcut()
  {
    TimeManager->setSpeed(0);
    if( TimeManager->getTurnPercent() != 0 && TimeManager->getTurnPercent() != 1 && TimeManager->getTurnPercent() != 0.5f )
    {
      TimeManager->setTurnPercent( 0.0f );
    }

    TimeManager->setTurnPercent( TimeManager->getTurnPercent() - 0.5f );
  }


  //Prepares the tabs and tables for the unit stats area
  void _GUI::initUnitStats()
  {
    //TODO Move this game-specific code out of _GUI

    //Create unit Stats tab area
    m_unitStatsArea = new QTabWidget( m_dockLayoutFrame );

    //Create tables to fill tabs
    m_globalStats = new QTableWidget(m_unitStatsArea);
    m_selectionStats = new QTableWidget(m_unitStatsArea);
    m_individualStats = new QTableWidget(m_unitStatsArea);

    //Create headers for tables
    m_globalStatsVerticalLabels<<"Player Gold"<<"Pirates"<<"Avg Pirate Health"<<"Avg Pirate Gold"
      <<"Total Pirate Gold"<<"Ships"<<"Avg Ship Health"<<"Avg Ship Gold"<<"Treasure Boxes";
    m_globalStatsHorizontalLabels<<"Total"<<"P0"<<"P1"<<"P2"<<"P3";
    m_selectionStatsVerticalLabels<<"Player Gold"<<"Pirates"<<"Avg Pirate Health"<<"Avg Pirate Gold"
      <<"Total Pirate Gold"<<"Ships"<<"Avg Ship Health"<<"Avg Ship Gold"<<"Treasure Boxes";
    m_selectionStatsHorizontalLabels<<"Total"<<"P0"<<"P1"<<"P2"<<"P3";
    m_individualStatsVerticalLabels<<"ID"<<"Owner"<<"Type"<<"Health"<<"Gold"<<"X"<<"Y";
    m_individualStatsHorizontalLabels<<".";

    //Set table properties and headers
    m_globalStats->setRowCount(m_globalStatsVerticalLabels.size());
    m_globalStats->setColumnCount(m_globalStatsHorizontalLabels.size());
    m_globalStats->setVerticalHeaderLabels ( m_globalStatsVerticalLabels );
    m_globalStats->setHorizontalHeaderLabels( m_globalStatsHorizontalLabels );

    m_selectionStats->setRowCount(m_selectionStatsVerticalLabels.size());
    m_selectionStats->setColumnCount(m_selectionStatsHorizontalLabels.size());
    m_selectionStats->setVerticalHeaderLabels ( m_selectionStatsVerticalLabels );
    m_selectionStats->setHorizontalHeaderLabels( m_selectionStatsHorizontalLabels );

    m_individualStats->setRowCount(m_individualStatsVerticalLabels.size());
    m_individualStats->setColumnCount(m_individualStatsHorizontalLabels.size());
    m_individualStats->setVerticalHeaderLabels ( m_individualStatsVerticalLabels );
    m_individualStats->setHorizontalHeaderLabels( m_individualStatsHorizontalLabels );

    //Add tabs of tables to tab area
    m_unitStatsArea->addTab( m_globalStats, "Global Stats" );
    m_unitStatsArea->addTab( m_selectionStats, "Selection Stats" );
    m_unitStatsArea->addTab( m_individualStats, "Individual Unit Stats" );

    //Add tab area to dockLayout
    m_dockLayout->addWidget( m_unitStatsArea );
  }


  ControlBar * _GUI::getControlBar()
  {
    return m_controlBar;
  }


  void _GUI::catchEscapeKey()
  {
    if(getFullScreen())
    {
      setFullScreen(false);
    }
  }


  bool _GUI::getFullScreen()
  {
    return fullScreen;
  }


  void _GUI::setFullScreen(bool value)
  {
    fullScreen = value;
    if(fullScreen)
    {
      m_normalWindowGeometry = geometry();
      showFullScreen();
    }
    else
    {
      showNormal();
      setGeometry(m_normalWindowGeometry);
    }
    show();

  }


  void _GUI::turnPercentageShortcut1(){turnPercentageCalc(0);};
  void _GUI::turnPercentageShortcut2(){turnPercentageCalc(1);};
  void _GUI::turnPercentageShortcut3(){turnPercentageCalc(2);};
  void _GUI::turnPercentageShortcut4(){turnPercentageCalc(3);};
  void _GUI::turnPercentageShortcut5(){turnPercentageCalc(4);};
  void _GUI::turnPercentageShortcut6(){turnPercentageCalc(5);};
  void _GUI::turnPercentageShortcut7(){turnPercentageCalc(6);};
  void _GUI::turnPercentageShortcut8(){turnPercentageCalc(7);};
  void _GUI::turnPercentageShortcut9(){turnPercentageCalc(8);};
  void _GUI::turnPercentageShortcut0(){turnPercentageCalc(9);};

  QTableWidget * _GUI::getIndividualStats()
  {
    return m_individualStats;
  }


  QTableWidget * _GUI::getSelectionStats()
  {
    return m_selectionStats;
  }


  QTableWidget * _GUI::getGlobalStats()
  {
    return m_globalStats;
  }

} // visualizer

