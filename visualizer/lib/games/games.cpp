#include "games.h"

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

#include <iostream>
using namespace std;

void _Games::_setup()
{
  IGame *game = 0;
  QDir pluginsDir( qApp->applicationDirPath() );
  pluginsDir.cd( "plugins" );
  foreach( QString fileName, pluginsDir.entryList( QDir::Files ) )
  {
#if __DEBUG__
    cerr << "Loading Plugin: " << qPrintable( pluginsDir.absoluteFilePath( fileName ) ) << endl;
#endif
    QPluginLoader pluginLoader( pluginsDir.absoluteFilePath( fileName ) );
    QObject *plugin = pluginLoader.instance();
    if( plugin )
    {
      game = qobject_cast<IGame *>( plugin );
      if( game )
      {
        game->loadGamelog( "log" );
        m_gameList.push_back( game );
      }
    }
  }
}

void _Games::destroy()
{
  delete Games;
  Games = 0;

}
