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
    IRenderer& r = *m_plant->Renderer;
    plant& p = *m_plant;

    r.setColor( 1, 1, 1, 1 );

    r.drawTexturedQuad( p.x, p.y, 1, 1, "plant" );

    if( p.flower )
    {
      r.drawTexturedQuad( p.x, p.y, 0.5, 0.5, "flower" );
    }

    if( p.leaf )
    {
      r.drawTexturedQuad( p.x + 0.5, p.y, 0.5, 0.5, "leaf" );
    }

    if( p.root )
    {
      r.drawTexturedQuad( p.x, p.y+0.5, 0.5, 0.5, "root" );
    }

  }

} // visualizer 

