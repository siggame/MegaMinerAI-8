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
#include "../objectmanager/objectmanager.h"
#include "../optionsmanager/optionsman.h"
#include "../renderer/renderer.h"
#include "../resourcemanager/resourceman.h"
#include "../resourcemanager/textureloader.h"

///////////////////////////////////////////////////////////////////////////////
/// @class _Games
/// @description This is the module for loading plugins
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @function _Games::_setup()
/// @brief Setup module which finds the plugins in the plugins directory
/// and loads them into memory.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @function _Games::gameList()
/// @brief Returns a vector of the games currently loaded into memory
///////////////////////////////////////////////////////////////////////////////

namespace visualizer
{

  class _Games: public Module
  {
    public:
    
      static void setup();
      void _setup();
      static void destroy();

      std::vector< IGame* >& gameList();

    private:
      std::vector< IGame* > m_gameList;

  };

  extern _Games *Games;

} // visualizer

#endif
