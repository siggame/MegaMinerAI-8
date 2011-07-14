#include "games.h"
#include <iostream>
using namespace std;

namespace visualizer
{

_Games *Games = 0;

void _Games::setup()
{
  if( !Games )
  {
    Games = new _Games;
  }
  else
  {
    THROW( Exception, "Games Loader is already initialized." );
  }

  Games->_setup();
}

void _Games::_setup()
{
  IGame *game = 0;
  bool pluginFound;
  QDir pluginsDir( qApp->applicationDirPath() );
  Interfaces intf;

  intf.gui = GUI;
  intf.objectManager = ObjectManager;
  intf.options = OptionsMan;
  intf.renderer = Renderer;
  intf.resourceManager = ResourceMan;
  intf.timeManager = TimeManager;

  pluginsDir.cd( "plugins" );
  foreach( QString fileName, pluginsDir.entryList( QDir::Files ) )
  {
    QPluginLoader pluginLoader( pluginsDir.absoluteFilePath( fileName ) );
    QObject *plugin = pluginLoader.instance();
    pluginFound = false;
    if( plugin )
    {
      game = qobject_cast<visualizer::IGame *>( plugin );
      if( game )
      {
#if __DEBUG__
      cerr << "Plugin Loaded: " << qPrintable( pluginsDir.absoluteFilePath( fileName ) ) << endl;
#endif
        pluginFound = true;
        m_gameList.push_back( game );
      }
    }

    if( !pluginFound )
    {
      THROW
        ( 
        Exception, 
        "Plugin: Did Not Load Correctly\n Path:  %s", 
        qPrintable( pluginsDir.absoluteFilePath( fileName ) )
        );
    }
  }
}

std::vector< IGame* > _Games::gameList()
{
  return m_gameList;
}

void _Games::destroy()
{
  delete Games;
  Games = 0;

}

} // visualizer
