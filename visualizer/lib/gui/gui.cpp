#include "gui.h"
#include "../games/games.h"
#include "../renderer/renderer.h"
#include "../parser/parser.h"
#include <QDesktopServices>
#include <Qt>
#include "../../piracy/piratemap.h"
#include "../../piracy/dupObj.h"

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>

using namespace std;

_GUI *GUI = 0;

_GUI::~_GUI()
{
  delete m_helpContents;
  delete m_centralWidget;
}


bool _GUI::reg( const std::string& id, guiObj *obj )
{
  if( m_objects.find( id ) != m_objects.end() )
    return false;

  m_objects[id] = obj;
  return true;
}


bool _GUI::del( const std::string& id )
{
  if( m_objects.find(id) == m_objects.end() )
    return false;

  m_objects.erase( id );
  return true;
}


bool _GUI::setup()
{
  if( !GUI )
  {
    GUI = new _GUI;
  } else
  {
    throw "GUI Already Setup";
  }

  GUI->m_isSetup = GUI->doSetup();
  return GUI->m_isSetup;
}


bool _GUI::clear()
{
  m_objects.clear();
  return true;
}


guiObj* _GUI::getGUIObject( const std::string& id )
{
  if( m_objects.find(id) == m_objects.end() )
    return NULL;

  return m_objects[id];
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


unsigned int _GUI::numObjects()
{
  return m_objects.size();
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


#include <iostream>
using namespace std;
void _GUI::loadGamelog( std::string gamelog )
{

#if 0
  if( !ObjectLoader::loadGamelog( gamelog ) )
  {
    std::cout << "THROWING SHITFIT: the gamelog \"" << gamelog << " wont load\n";
  }
#endif
  return;                        //! @todo throw shitfit
}


void _GUI::update()
{
  m_controlBar->update();
}


void _GUI::dropEvent( QDropEvent* evt )
{

  evt->mimeData()->text();
  string data = evt->mimeData()->text().toAscii().constData();
  loadGamelog( data );

  // TODO: Open the gamelog with the appropriate plugins

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
    tr( "Gamelogs (*.gamelog);;All Files (*.*)") ).toAscii().constData();

  if( filename.size() > 0 )
  {
    m_previousDirectory = filename;

    ofstream dirinfoOUT;
    dirinfoOUT.open("dirinfo.txt");
    dirinfoOUT << m_previousDirectory.toStdString();
    dirinfoOUT.close();
    cout << filename.toStdString() << endl;
    loadGamelog( filename.toStdString() );
  }

}


bool _GUI::doSetup()
{

  setAcceptDrops( true );

  m_centralWidget = new CentralWidget( this );
  setCentralWidget( m_centralWidget );
  createActions();
  buildControlBar();

  createMenus();
  buildToolSet();

  // If we're in arenaMode, change some settings
  if(
    !OptionsMan->exists( "arenaMode" ) ||
    OptionsMan->getBool( "arenaMode" )
    )
  {
    menuBar()->hide();
    setFullScreen(true);
    m_dockWidget->hide();
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
  // Get the toolset widget if it exists
  m_toolSetWidget =
    (GOCFamily_GUIToolSet*)getGUIObject( "ToolSet" );

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

  //Add Unit Stats to the layout
  initUnitStats();

  // If we have our tools for this game, add those bitches
  if( m_toolSetWidget )
  {
    m_dockLayout->addWidget( m_toolSetWidget );
  }

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
  if(TimeManager->getTurn() < TimeManager->getNumTurns()-1)
  {
    TimeManager->setTurn(TimeManager->getTurn() + 1);
  }
}


void _GUI::stepTurnBackShortcut()
{
  if(TimeManager->getTurn() > 0)
  {
    TimeManager->setTurn(TimeManager->getTurn() - 1);
  }
}


//Prepares the tabs and tables for the unit stats area
void _GUI::initUnitStats()
{
  //TODO: Move this game-specific code out of _GUI

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
