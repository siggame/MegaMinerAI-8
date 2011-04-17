#ifndef SCOREBOARD_H
#define SCOREBOARD_H
#include "../lib/gocfamily_render.h"

class Scoreboard : public GOCFamily_Render
{
  const GOC_IDType componentID() const { return GOC_IDType( "ScoreboardRender" ); }

  void update();
  void renderAt( const unsigned int& turn, const unsigned int& frame );


};

#endif
