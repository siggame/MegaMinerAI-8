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

#include <iostream>
using namespace std;

void _Games::_setup()
{
  IGame *game = 0;
  QDir pluginsDir( qApp->applicationDirPath() );
  pluginsDir.cd( "plugins" );
  foreach( QString fileName, pluginsDir.entryList( QDir::Files ) )
  {
    cout << qPrintable( pluginsDir.absoluteFilePath( fileName ) ) << endl;
    QPluginLoader pluginLoader( pluginsDir.absoluteFilePath( fileName ) );
    QObject *plugin = pluginLoader.instance();
    if( plugin )
    {
      cout << "PLUGIN" << endl;
      game = qobject_cast<IGame *>( plugin );
      if( game )
      {
        cout << "GAME" << endl;
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
