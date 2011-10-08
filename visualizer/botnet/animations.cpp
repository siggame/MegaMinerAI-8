#include "animations.h"
#include "easing_equations.h"

namespace visualizer
{
  void StartAnim::animate( const float& t, AnimData *d )
  {
    VirusData *v = (VirusData*)d;
  } // StartAnim::animate()

  void DrawVirus::animate( const float& t, AnimData *d )
  {
    VirusData *vd = (VirusData*)d;
    virus &v = *m_virus;
    
    if( v.owner == 0 )
       v.renderer().setColor( Color( 1, 0, 0 ) );
    else
       v.renderer().setColor( Color( 0, 0, 1 ) );
    
    v.renderer().drawQuad( vd->x, vd->y, 1, 1 );
  } // DrawVirus::animate()

  void DrawTile::animate( const float& t, AnimData *d )
  {

    tile &q = *m_tile;

    if( q.owner == 0 )
      q.renderer().setColor( Color( 0.5, 0, 0 ) ); 
    else if( q.owner == 1 )
      q.renderer().setColor( Color( 0, 0, 0.5 ) );
    else if( q.owner == 2 )
      q.renderer().setColor( Color( 0.1, 0.1, 0.1 ) );
    else if( q.owner == 3 )
      q.renderer().setColor( Color( 0.5, 0.7, 0.2 ) );
    
    q.renderer().drawQuad( q.x, q.y, 1, 1 );
  } // DrawTile::animate()

  void LeftAnim::animate( const float& t, AnimData *d )
  {
    VirusData *v = (VirusData*)d;
    if( t > startTime && t < endTime )
    {
      v->x = linearTween( t-startTime, v->x, -1, endTime-startTime );
    } else if ( t >= endTime )
    {
      v->x--;
    }
  } // LeftAnim::animate()

  void RightAnim::animate( const float& t, AnimData *d )
  {
    VirusData *v = (VirusData*)d;
    if( t > startTime && t < endTime )
    {
      v->x = linearTween( t-startTime, v->x, 1, endTime-startTime );
    } else if( t >= endTime )
    {
      v->x++;
    }
  } // RightAnim::animate() 

  void UpAnim::animate( const float& t, AnimData *d )
  {
    VirusData *v = (VirusData*)d;
    if( t > startTime && t < endTime )
    {
      v->y = linearTween( t-startTime, v->y, 1, endTime-startTime );
    } else if( t >= endTime )
    {
      v->y++;
    }
  } // UpAnim::animate()

  void DownAnim::animate( const float& t, AnimData *d )
  {
    VirusData *v = (VirusData*)d;
    if( t > startTime && t < endTime )
    {
      v->y = linearTween( t-startTime, v->y, -1, endTime-startTime );
    } else if( t >= endTime )
    {
      v->y--;
    }
  } // DownAnim::animate()

} // visualizer


