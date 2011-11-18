#include "games.h"
#include <iostream>
using namespace std;
#ifdef Q_WS_MAC
#include <CoreFoundation/CoreFoundation.h>
#endif

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
  } // _Games::setup()

  void _Games::_setup()
  {
    IGame *game = 0;
    bool pluginFound;

    QDir pluginsDir( qApp->applicationDirPath() );
    QStringList pluginFilter;

    pluginFilter << "*.dll" << "*.so" << "*.dylib";
    pluginsDir.setNameFilters(pluginFilter);

    pluginsDir.cd( "plugins" );
    foreach( QString fileName, pluginsDir.entryList( QDir::Files ) )
    {
      QPluginLoader& pluginLoader = *new QPluginLoader( pluginsDir.absoluteFilePath( fileName ) );
      m_plugins.push_back( &pluginLoader );
      //QPluginLoader pluginLoader( pluginsDir.absoluteFilePath( fileName ) );
      QObject *plugin = pluginLoader.instance();
      if( plugin )
      {
        game = qobject_cast<IGame *>( plugin );
        if( game )
        {
#if __DEBUG__
          cerr << "Plugin Loaded: " << qPrintable( pluginsDir.absoluteFilePath( fileName ) ) << endl;
#endif
          pluginFound = true;
          m_gameList.push_back( game );
          game->gui = GUI;
          game->animationEngine = AnimationEngine;
          game->options = OptionsMan;
          game->renderer = Renderer;
          game->resourceManager = ResourceMan;
          game->textureLoader = TextureLoader;
          game->timeManager = TimeManager;
        } 
        else
        {
          cerr << "Plugin Is Not Valid For Usage" << endl;
          cerr << " Path: " << qPrintable( pluginsDir.absoluteFilePath( fileName ) ) << endl;
          cerr << " Error String: " << endl << "  " << qPrintable( pluginLoader.errorString() ) << endl;
        }
      }
      else
      {
        cerr << "Plugin Could Not Be Loaded Into Memory" << endl;
        cerr << " Path:  " << qPrintable( pluginsDir.absoluteFilePath( fileName ) ) << endl;
        cerr << " Error String: " << endl;
        cerr << "  " << qPrintable( pluginLoader.errorString() ) << endl;
      }
    }
    
  } // _Games::_setup()

  std::vector< IGame* >& _Games::gameList()
  {
    return m_gameList;
  } // _Games::gameList()

  void _Games::destroy()
  {
    delete Games;
    Games = 0;

  } // _Games::destroy()

  _Games::~_Games()
  {
    for
      ( 
      vector< QPluginLoader* >::iterator i = m_plugins.begin();
      i != m_plugins.end();
      i++ 
      )
    {
      (*i)->unload();
      delete *i;
    }

  }

} // visualizer
