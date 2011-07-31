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
