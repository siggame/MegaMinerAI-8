#ifndef SCOREBOARD_H
#define SCOREBOARD_H
#include "./parser/structures.h"
#include "../lib/gocfamily_render.h"
#include "../lib/renderer/textRenderer/drawGLFont.h"
#include <QWaitCondition>
#include <list>
#include <iostream>
using namespace std;

namespace visualizer
{

struct Score
{
  int p0gold;
  int p1gold;
  int p0time;
  int p1time;

};

class Scoreboard : public GOCFamily_Render
{
  public:
    const GOC_IDType componentID() const { return GOC_IDType( "ScoreboardRender" ); }

    void loadFont( int fontTex, string fontWidthsFile );

    void update();
    void renderAt( const unsigned int& turn, const unsigned int& frame );

    void drawStart();
    void drawEnd();

    void parseScores( Game& g );

    vector<Score> scores;

    Player player[2];
    int winner;
    string winReason;

  private:
    DrawGLFont fnt;

};

} // visualizer

#endif
