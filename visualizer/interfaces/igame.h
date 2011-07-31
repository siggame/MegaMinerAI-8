#ifndef IGAME_H
#define IGAME_H

#include "ianimationengine.h"
#include "iobjectmanager.h"
#include "irenderer.h"
#include "iresourceman.h"
#include "icentralwidget.h"
#include "igui.h"
#include "ioptionsman.h"
#include "itextureloader.h"
#include "itimemanager.h"
#include <QtPlugin>
#include <string>

namespace visualizer
{

  struct LogRegex
  {
    unsigned int  startSize;
    std::string   regex;
  };

  struct Interfaces
  {
    IAnimationEngine *animationEngine;
    IGUI *gui;
    IObjectManager *objectManager;
    IOptionsMan *options;
    IRenderer *renderer;
    IResourceMan *resourceManager;
    ITextureLoader *textureLoader;
    ITimeManager *timeManager;
  };

  // This will act as the initial interface between the visualizer
  // and the game specific code.

  class IGame
  {
    public:
      virtual LogRegex logFileInfo() = 0;
      virtual void loadGamelog( std::string gamelog ) = 0;
      virtual void registerInterfaces( Interfaces intf ) = 0;
  };

} // visualizer

Q_DECLARE_INTERFACE( visualizer::IGame, "siggame.vis2.game/0.1" );


#endif
