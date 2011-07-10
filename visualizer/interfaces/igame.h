#ifndef IGAME_H
#define IGAME_H

#include <QtPlugin>
#include <string>

struct LogRegex
{
  unsigned int  startSize;
  std::string   regex;
};

// This will act as the initial interface between the visualizer
// and the game specific code.

class IGame
{
  public:
    virtual LogRegex logFileInfo() = 0;
    virtual void loadGamelog( std::string gamelog ) = 0;
};

Q_DECLARE_INTERFACE( IGame, "siggame.vis2.game/0.1" );

#endif
