#ifndef IGAME_H
#define IGAME_H

#include <QtPlugin>

// This will act as the initial interface between the visualizer
// and the game specific code.

class IGame
{

  public:
};

Q_DECLARE_INTERFACE( IGame, "siggame.vis2.game/0.1" );

#endif
