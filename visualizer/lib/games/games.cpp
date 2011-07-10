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
    throw "Games Loader is already initialized.";
  }

  Games->_setup();
}

void _Games::_setup()
{
  IGame *game = 0;
  QDir pluginsDir( qApp->applicationDirPath() );
  pluginsDir.cd( "plugins" );
  foreach( QString fileName, pluginsDir.entryList( QDir::Files ) )
  {
    QPluginLoader pluginLoader( pluginsDir.absoluteFilePath( fileName ) );
    QObject *plugin = pluginLoader.instance();
    if( plugin )
    {
      game = qobject_cast<IGame *>( plugin );
      if( game )
      {
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
