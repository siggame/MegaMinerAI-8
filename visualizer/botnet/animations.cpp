#include "animations.h"

namespace visualizer
{
  void StartAnim::animate( const float& t, AnimData *d )
  {
  }

  void DrawVirus::animate( const float& t, AnimData *d )
  {
    virus &v = *m_virus;
    
    if( v.owner == 0 )
       v.renderer().setColor( Color( 1, 0, 0 ) );
    else
       v.renderer().setColor( Color(0, 0, 1) );
    
    v.renderer().drawQuad( v.x, v.y, 1, 1);
  }
} // visualizer


