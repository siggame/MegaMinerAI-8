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
<<<<<<< HEAD
	QStringList pluginFilter;

	pluginFilter << "*.dll" << "*.so";
	pluginsDir.setNameFilters(pluginFilter);
=======
#ifdef Q_WS_MAC
	pluginsDir.cd( "../../../" );
     
#endif
>>>>>>> c1f46184f9485b31073e83b036f4e6d5e81642af

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
#if __DEBUG__
          cerr << "Plugin Loaded: " << qPrintable( pluginsDir.absoluteFilePath( fileName ) ) << endl;
#endif
          pluginFound = true;
          m_gameList.push_back( game );
          game->gui = GUI;
          game->animationEngine = AnimationEngine;
          game->objectManager = ObjectManager;
          game->options = OptionsMan;
          game->renderer = Renderer;
          game->resourceManager = ResourceMan;
          game->textureLoader = TextureLoader;
          game->timeManager = TimeManager;
        } 
        else
        {
          THROW
            ( 
            Exception, 
            "Plugin Is Not Valid For Usage\n Path:  %s\n Error String: \n  %s", 
            qPrintable( pluginsDir.absoluteFilePath( fileName ) ),
            qPrintable( pluginLoader.errorString() )
            );
        }
      }
      else
      {
        THROW
          ( 
          Exception, 
          "Plugin Could Not Be Loaded Into Memory\n Path:  %s\n Error String: \n  %s", 
          qPrintable( pluginsDir.absoluteFilePath( fileName ) ),
          qPrintable( pluginLoader.errorString() )
          );
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

} // visualizer
