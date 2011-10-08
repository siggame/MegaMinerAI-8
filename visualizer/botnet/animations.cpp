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
    tile &q = *m_tile;

    if( q.owner == 0)
      q.renderer().setColor( Color(0.5, 0, 0) ); 
    else if ( q.owner == 1)
      q.renderer().setColor( Color(0  , 0 , 0.5 ) );
    else if ( q.owner == 2)
      q.renderer().setColor( Color(0.1 ,0.1 ,0.1 ) );
    else if ( q.owner == 3)
      q.renderer().setColor( Color(0.5 ,0.7 ,0.2 ) );
    
    q.renderer().drawQuad( q.x, q.y, 1, 1);
  }
} // visualizer


