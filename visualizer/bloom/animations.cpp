#include "animations.h"
#include <iostream>
using namespace std;

namespace visualizer
{

  void StartAnim::animate( const float& t, AnimData *d )
  {
    
  }

  void DrawGround::animate( const float& t, AnimData *d )
  {
    IRenderer& r = *m_dirt->Renderer;
    r.setColor( 1, 1, 1, 1 );

    r.drawTexturedQuad( 0, 0, 30, 30, "dirt" );
  }

  void DrawAnim::animate( const float& t, AnimData *d )
  {

  }

} // visualizer 

