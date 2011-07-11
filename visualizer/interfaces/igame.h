#ifndef IGAME_H
#define IGAME_H

#include "iobjectmanager.h"
#include "irenderer.h"
#include "iresourceman.h"
#include "icentralwidget.h"
#include "igui.h"
#include "ioptionsman.h"
#include "itimemanager.h"
#include <QtPlugin>
#include <string>

struct LogRegex
{
  unsigned int  startSize;
  std::string   regex;
};

struct Interfaces
{
  IGUI *gui;
  IObjectManager *objectManager;
  IOptionsMan *options;
  IRenderer *renderer;
  IResourceMan *resourceManager;
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

Q_DECLARE_INTERFACE( IGame, "siggame.vis2.game/0.1" );

#endif
