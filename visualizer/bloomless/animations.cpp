#include "animations.h"

namespace visualizer
{
  void StartAnim::animate( const float& /* t */, AnimData * /* d */ )
  {
  }

  void DrawPlant::animate( const float& /* t */, AnimData * /* d */ )
  {

    plant &p = *m_plant;

    float r = 0;
    float g = 0;
    float b = 0;

    p.renderer().setColor( Color( 1, 1, 1 ) );
    if( p.ownerID == 0 )
    {
      p.renderer().drawTexturedQuad( p.x, p.y, 1, 1, "shipRed" );
    } else
    {
      p.renderer().drawTexturedQuad( p.x, p.y, 1, 1, "shipGreen" );
    }

#if 0
    if( p.flower )
    {
      b = 1;
    }

    if( p.leaf )
    {
      g = 1;
    }

    if( p.root )
    {
      r = 1;
    }
#endif


    p.renderer().setColor( Color( 0, 1, 0 ) );
    p.renderer().drawProgressBar( p.x + 0.04, p.y+ 0.04, .92, 0.08, p.health/20.0f, Color( 0, 0, 0, .8 ) );

  }

}
