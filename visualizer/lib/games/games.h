///////////////////////////////////////////////////////////////////////////////
/// @file games.h
/// @description Contains the module for loading plugins for game 
/// implementations
///////////////////////////////////////////////////////////////////////////////
#ifndef GAMES_H
#define GAMES_H

#include <QtGui>

#include "common.h"
#include "igame.h"
#include "../animationengine/animationengine.h"
#include "../gui/gui.h"
#include "../optionsmanager/optionsman.h"
#include "../renderer/renderer.h"
#include "../resourcemanager/resourceman.h"
#include "../resourcemanager/textureloader.h"
namespace visualizer
{

///////////////////////////////////////////////////////////////////////////////
/// @class _Games
/// @description This is the module for loading plugins
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn _Games::_setup()
/// @brief Setup module which finds the plugins in the plugins directory
/// and loads them into memory.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn _Games::gameList()
/// @brief Returns a vector of the games currently loaded into memory
///////////////////////////////////////////////////////////////////////////////


  class _Games: public Module
  {
    public:
    
      static void setup();
      void _setup();
      static void destroy();

      ~_Games();

      std::vector< IGame* >& gameList();

    private:
      std::vector< IGame* > m_gameList;
      std::vector< QPluginLoader* > m_plugins;

  };

  extern _Games *Games;

} // visualizer

#endif
