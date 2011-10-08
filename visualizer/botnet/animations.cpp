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
  void DrawTile::animate( const float& t, AnimData *d )
  {
    tile &t = *m_tile;

    if( t.owner == 0)
      t.renderer().setColor( Color(0.5, 0, 0) ); 
    else if ( t.owner == 1)
      t.renderer().setColor( Color( , , ) );
    else if ( t.owner == 2)
      t.renderer().setColor( Color( , , ) );
    else if ( t.owner == 3)
      t.renderer().setColor( Color( , , ) );
    
    t.renderer().drawQuad( t.x, t.y, 1, 1);
  }
} // visualizer


