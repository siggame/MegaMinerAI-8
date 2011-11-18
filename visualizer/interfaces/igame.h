#ifndef IGAME_H
#define IGAME_H

#include "ianimationengine.h"
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

  class IGame
  {
    public:
      virtual LogRegex logFileInfo() = 0;
      virtual void loadGamelog( std::string gamelog ) = 0;
    
      IAnimationEngine *animationEngine;
      IGUI *gui;
      IOptionsMan *options;
      IRenderer *renderer;
      IResourceMan *resourceManager;
      ITextureLoader *textureLoader;
      ITimeManager *timeManager;

  };

} // visualizer

Q_DECLARE_INTERFACE( visualizer::IGame, "siggame.vis2.game/0.1" );


#endif
