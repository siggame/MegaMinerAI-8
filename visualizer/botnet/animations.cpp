#include "animations.h"
#include "easing_equations.h"

#include <sstream>

namespace visualizer
{
  void StartAnim::animate( const float& t, AnimData *d )
  {
  } // StartAnim::animate()

  void DrawVirus::animate( const float& t, AnimData *d )
  {
    VirusData *vd = (VirusData*)d;
    virus &v = *m_virus;
    std:stringstream level;
    level << v.level;
    
    if ( v.owner == 0 )
    {
      v.renderer().setColor( Color( 1, 0.1, 0.1, .8 ) );
      v.renderer().drawQuad( vd->x+0.25, vd->y+0.25, .25, .5 );
      v.renderer().setColor( Color( 0, 0, 0 ) );
      v.renderer().drawText( vd->x+0.25, vd->y+0.25, "mainFont", level.str()  );
    }
    else
    {
      v.renderer().setColor( Color( 0.1, 0.1, 1, .8 ) );
      v.renderer().drawQuad( vd->x+0.50, vd->y+0.25, .25, .5 );
      v.renderer().setColor( Color( 0, 0, 0 ) );
      v.renderer().drawText( vd->x+0.50, vd->y+0.25, "mainFont", level.str()  );
    }
    
  } // DrawVirus::animate()

  void Appear::animate( const float& t, AnimData *d )
  {
    GeneralAnim* g = (GeneralAnim*)d;

    if( t < startTime )
    {
      g->alpha = 0;
    } else
    if( t > endTime )
    {
      g->alpha = 1;
    } else
    {
      g->alpha = easeOutBounce( t-startTime, 0, 1, endTime-startTime );
    } 

    g->alpha = 1;
     

  }

  void DrawBase::animate( const float& t, AnimData *d )
  {

    GeneralAnim *g = (GeneralAnim*) d;
    base &q = *m_base;

    float intensity;
    if( t < 0.5 )
    {
      intensity = easeOutCubic( t, .8, .2, 0.5 );
    } else
    {
      intensity = easeInCubic( t-.5, 1, -.2, 0.5 );
    }

    if( q.owner == 0 )
    {
      q.renderer().setColor( Color( 0.3f*intensity, 0, 0, 1 ) ); 
    }
    else if( q.owner == 1 )
    {
      q.renderer().setColor( Color( 0, 0, 0.3f*intensity, 1 ) );
    }

    q.renderer().drawQuad( q.x+.1, q.y+.1, .8, .8 );
  } // DrawBase::animate()

  void DrawTile::animate( const float& t, AnimData *d )
  {

    GeneralAnim *g = (GeneralAnim*) d;
    tile &q = *m_tile;

    if( q.owner == 0 )
    {
      if( q.connected() )
        q.renderer().setColor( Color( 0.4, 0, 0, g->alpha ) ); 
      else
        q.renderer().setColor( Color( 0.2, 0, 0, g->alpha ) );
    }
    else if( q.owner == 1 )
    {
      if( q.connected() )
        q.renderer().setColor( Color( 0, 0, 0.4, g->alpha ) );
      else
        q.renderer().setColor( Color( 0, 0, 0.2, g->alpha ) );
    }
    else if( q.owner == 2 )
      // NOTHING
      q.renderer().setColor( Color( 0.1, 0.1, 0.1, 0.0 ) );
    else if( q.owner == 3 )
      // WALLS
      q.renderer().setColor( Color( 0.5, 0.5, 0.4 ) );
  
    q.renderer().drawQuad( q.x, q.y, 1, 1 );
  } // DrawTile::animate()

  void LeftAnim::animate( const float& t, AnimData *d )
  {
    VirusData *v = (VirusData*)d;
    if( t > startTime && t < endTime )
    {
      v->x = easeOutCubic( t-startTime, v->x, -1, endTime-startTime );
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
      v->x = easeOutCubic( t-startTime, v->x, 1, endTime-startTime );
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
      v->y = easeOutCubic( t-startTime, v->y, 1, endTime-startTime );
    } else if( t >= endTime )
    {
      v->y++;
    }
  } // UpAnim::animate()

  void DownAnim::animate( const float& t, AnimData *d )
  {
    // I think this is actually up
    VirusData *v = (VirusData*)d;
    if( t > startTime && t < endTime )
    {
      v->y = easeOutCubic( t-startTime, v->y, -1, endTime-startTime );
    } else if( t >= endTime )
    {
      v->y--;
    }
  } // DownAnim::animate()

  void DrawBackground::animate( const float& t, AnimData *d )
  {
    for ( int x = 0; x < m_background->mapWidth; x += 4 )
    {
      for ( int y = 0; y < m_background->mapHeight; y+= 4 )
      {
        cout << "I'm in the Y loop! at: " << x << "," << y << "\n";
        m_background->renderer().setColor( Color( 0.05, 0.05, 0.05 ) );
        m_background->renderer().drawQuad( x, y, 4, 4 );
        
        m_background->renderer().setColor( Color( 1.0, 1.0, 1.0 ) );
        m_background->renderer().drawTexturedQuad( x, y, 4, 4 , "nodeBackground" );
      }
    }
  } 

} // visualizer


