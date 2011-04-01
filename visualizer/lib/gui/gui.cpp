#include "gui.h"
#include "../renderer/renderer.h"
#include "../parser/parser.h"
#include <QDesktopServices>
#include "../../piracy/boatdata.h"
#include "../../piracy/boatrender.h"
#include "../../piracy/piratedata.h"
#include "../../piracy/piraterender.h"

#include <iostream>
#include <string>
using namespace std;

GUI::~GUI()
{
  delete m_helpContents;
  delete m_centralWidget;
}

bool GUI::reg( const std::string& id, guiObj *obj )
{
  if( !isInit() )
    return false;

  if( get()->m_objects.find( id ) != get()->m_objects.end() )
    return false;

  get()->m_objects[id] = obj;
  return true;
}

bool GUI::del( const std::string& id )
{
  if( !isInit() )
    return false;

  if( get()->m_objects.find(id) == get()->m_objects.end() )
    return false;

  get()->m_objects.erase( id );
  return true;
}

bool GUI::setup()
{
  if( !isInit() )
    return false;

  return get()->doSetup();
}

bool GUI::clear()
{
  if( !isInit() )
    return false;

  get()->m_objects.clear();
  return true;
}

guiObj* GUI::getGUIObject( const std::string& id )
{
  if( !isInit() )
    return NULL;

  if( get()->m_objects.find(id) == get()->m_objects.end() )
    return NULL;

  return get()->m_objects[id];
}

bool GUI::create()
{
  if( !Singleton<GUI>::create() )
    return false;
  return setup();
}

bool GUI::destroy()
{
  if( !isInit() )
    return false;
  if( !clear() )
    return false;

  return Singleton<GUI>::destroy();
}

unsigned int GUI::numObjects()
{
  if( !isInit() )
    return 0;

  return get()->m_objects.size();
}

bool GUI::isSetup()
{
  if( !isInit() )
    return false;

  return get()->m_isSetup;
}
void GUI::dragEnterEvent( QDragEnterEvent* evt )
{
  // We may want to filter what's dropped on the window at some point
  evt->acceptProposedAction();
}

#include <iostream>
using namespace std;
void GUI::loadGamelog( std::string gamelog )
{
  Game g;
  parseFile( g, gamelog.c_str() );
  // Gamespecific stuff which need a removing

  if( !Renderer::isSetup() )
  {
    Renderer::create();
  }

  int pirateId = 0;
  int boatId = 0;
  int boats = 0;
  int pirates = 0;
  //cout << "Number of Turns: " << g.states.size() << endl;
  for( int i = 0; i < g.states.size(); i++ )
  {
    for( std::map<int,Pirate>::iterator p = g.states[i].pirates.begin();
        p != g.states[i].pirates.end();
        p++
       )
    {
      if( p->second.id > pirateId )
      {
        pirateId = p->second.id;
        GameObject *go = new GameObject( pirateId );
        PirateData *pd = new PirateData();
        pd->parsePirate( g, pirateId );
        PirateRender *pr = new PirateRender();
        pd->setOwner( go );
        pr->setOwner( go );
        go->setGOC( pd );
        go->setGOC( pr );
        Renderer::reg( pirateId, go );

        pirates++;

      }
    }

    for( std::map<int,Ship>::iterator s = g.states[i].ships.begin();
        s != g.states[i].ships.end();
        s++ )
    {
      if( s->second.id > boatId )
      {
        boatId = s->second.id;
        GameObject *go  = new GameObject( boatId );
        BoatData *bd = new BoatData();
        bd->parseBoat( g, boatId );
        BoatRender *br = new BoatRender();
        
        bd->setOwner( go );
        br->setOwner( go );
        go->setGOC( bd );
        go->setGOC( br );

        Renderer::reg( boatId, go );

        boats++;
      }

    }

  }

  cout << "Boats: " << boats << ", Pirates: " << pirates << endl;

}

void GUI::dropEvent( QDropEvent* evt )
{

  evt->mimeData()->text();
  string data = evt->mimeData()->text().toAscii().constData();
  loadGamelog( data );

  // TODO: Open the gamelog with the appropriate plugins

}

void GUI::resizeEvent( QResizeEvent* evt )
{
  QMainWindow::resizeEvent( evt );

}

void GUI::helpContents()
{
  if( optionsMan::isInit() &&
      optionsMan::exists( "helpURL" ) )
  {
    QDesktopServices::openUrl( QUrl( optionsMan::getStr( "helpURL" ).c_str() ) );
  } else
  {
    QDesktopServices::openUrl( QUrl( "http://www.megaminerai.com" ) );
  }
}

void GUI::fileOpen()
{

  string filename = QFileDialog::getOpenFileName( 
      this, 
      tr( "Open Gamelog" ),
      QDir::currentPath(),
      tr( "Gamelogs (*.gamelog);;All Files (*.*)") ).toAscii().constData();

  if( filename.size() > 0 )
  {
    loadGamelog( filename );
  }

}

bool GUI::doSetup()
{

  setAcceptDrops( true );

  m_centralWidget = new CentralWidget( this );
  setCentralWidget( m_centralWidget );
  createActions();
  createMenus();

  buildToolSet();

  setWindowState( 
      windowState() 
      | Qt::WindowActive 
      | Qt::WindowMaximized 
      );

  show();
  return true;
}

void GUI::createActions()
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

  m_fileExit = new QAction( tr( "E&xit" ), this );
  m_fileExit->setShortcut( tr( "Ctrl+X" ) );
  m_fileExit->setStatusTip( 
      tr( "Close the Visualizer" )
      );
  connect( m_fileExit, SIGNAL(triggered()), this, SLOT(close()) );

}

void GUI::createMenus()
{
  QMenu *menu;
  menu = menuBar()->addMenu( tr( "&File" ) );
  menu->addAction( m_fileOpen );
  menu->addSeparator();
  menu->addAction( m_fileExit );

  menu = menuBar()->addMenu( tr( "&Edit" ) );

  menu = menuBar()->addMenu( tr( "&View" ) );

  menu = menuBar()->addMenu( tr( "&Help" ) );
  menu->addAction( m_helpContents );
  
}

void GUI::buildToolSet()
{
  // Get the toolset widget if it exists 
  m_toolSetWidget =
    (GOCFamily_GUIToolSet*)GUI::getGUIObject( "ToolSet" );

  // If we're in arenaMode, don't even bother setting this up 
  if( 
      !optionsMan::isInit() || 
      !optionsMan::exists( "arenaMode" ) ||
      !optionsMan::getBool( "arenaMode" )
    )  
  {
    // Create the dock
    m_dockWidget = new QDockWidget( this );
    // Give it a frame to hold a layout
    m_dockLayoutFrame = new QFrame( m_dockWidget );
    // Give this frame a layout
    m_dockLayout = new QHBoxLayout( m_dockLayoutFrame );
    // Console area to the left
    m_consoleArea = new QTextEdit( m_dockLayoutFrame );
    // Allow users to stupidly move this as small as they like
    m_dockWidget->setMinimumHeight( 0 );

    // Add Buffer so we don't feel clausterphobic
    m_dockLayout->setContentsMargins( 2, 0, 2, 0 );

    // Add the console to the layout
    m_dockLayout->addWidget( m_consoleArea );

    // If we have our tools for this game, add those bitches
    if( m_toolSetWidget )
    {
      m_dockLayout->addWidget( m_toolSetWidget );
    }

    // Add the frame to the actual dock
    m_dockWidget->setWidget( m_dockLayoutFrame );
    // Add the dock to the main window
    addDockWidget( Qt::BottomDockWidgetArea, m_dockWidget );

  }
}
