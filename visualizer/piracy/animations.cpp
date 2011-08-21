#include "animations.h"

namespace visualizer
{

  // A Macros may be useful for this.  I dunno.
  void StartAnim::animate( const float& t, AnimData *d )
  {
    PirateData& data = ((PirateData&)*d);
    data.x = m_stack->a_x;
    data.y = m_stack->a_y;

  } // StartAnim::animate()

  void LeftAnim::animate( const float& t, AnimData *d )
  {
    // An interesting idea for ship animations is letting the ship animations 
    // sort of draw out at the end past their controlled duration time. 
    // When these bleed over into another move animation, the ship won't appear
    // to slow down, but just smoothly continue on.  It can't be too long, or 
    // ships will collide with each other on turns. 
    //
    // Eventually we should move this stuff into configuration that can be 
    // modified with a tool.
    // Hard coding animations are a thing of the past.
    PirateData& data = ((PirateData&)*d);
    if( t >= endTime )
    {
      data.x--;
    }
    else if( t >= startTime )
    {
      //cout << "LEFT: " << (t-startTime)/(endTime-startTime) << endl;
      data.x -= (t-startTime)/(endTime-startTime);
    }


    // if( m_ships > 0 )
    /*
    {
      interp_sigmoid( blah, m_startTime, m_endTime, t );
    } 
    else
    {
      interp_lin( m_startTime, m_endTime, t );
    }
    */
    // Need interpolation helper functions
    //interpolate( m_startTime, m_endTime, t );
    //interpolate_exp( param, m_startTime, m_endTime, t );
    //interpolate_sigmoid( param, m_startTime, m_endTime, t );
  }

  void RightAnim::animate( const float& t, AnimData *d )
  {
    PirateData& data = ((PirateData&)*d);
    if( t >= endTime )
    {
      data.x++;
    }
    else if( t >= startTime )
    {
      data.x += (t-startTime)/(endTime-startTime);
    }
  }

  void UpAnim::animate( const float& t, AnimData *d )
  {
    PirateData& data = ((PirateData&)*d);
    if( t >= endTime )
    {
      data.y--;
    }
    else if( t >= startTime )
    {
      data.y -= (t-startTime)/(endTime-startTime);
    }

  }

  void DownAnim::animate( const float& t, AnimData *d )
  {
    PirateData& data = ((PirateData&)*d);
    if( t >= endTime )
    {
      data.y++;
    }
    else if( t >= startTime )
    {
      data.y += (t-startTime)/(endTime-startTime);
    }

  }

  void AttackAnim::animate( const float& t, AnimData *d )
  {
    PirateData& data = ((PirateData&)*d);
  }

  void TalkAnim::animate( const float& t, AnimData *d )
  {
    PirateData& data = ((PirateData&)*d);
  }

  void DrawStack::animate( const float& t, AnimData *d )
  {
    PirateData& data = ((PirateData&)*d);
    IRenderer &r = *m_stack->Renderer;

    if( m_stack->m_owner == 0 )
      r.setColor( 1, 0, 0 );
    else if( m_stack->m_owner == 1 )
      r.setColor( 0, 1, 0 );
    else
      r.setColor( 0, 0, 1 );

    r.setColor( 1, 1, 1 );


    if( m_stack->m_ships )
    {
      if( m_stack->m_pirates )
      {
        // Draw Pirate On Top
        
      }
      // Draw Ship

      if( m_stack->m_owner == 0 )
      {
        r.drawTexturedQuad( data.x, data.y, 1, 1, "shipGreen" );
      } 
      else if( m_stack->m_owner == 1 )
      {
        r.drawTexturedQuad( data.x, data.y, 1, 1, "shipRed" );
      }
      else if( m_stack->m_owner == 2 || m_stack->m_owner == 3 )
      {
        r.drawTexturedQuad( data.x, data.y, 1, 1, "shipNPC" );
      }
      else
      {
        r.drawTexturedQuad( data.x, data.y, 1, 1, "portNPC" );
      }
    }
    else if( m_stack->m_pirates )
    {
      if( m_stack->m_owner == 0 )
      {
        r.drawTexturedQuad( data.x, data.y, 1, 1, "pirateGreen" );
      } 
      else if( m_stack->m_owner == 1 )
      {
        r.drawTexturedQuad( data.x, data.y, 1, 1, "pirateRed" );
      }
      else if( m_stack->m_owner == 2 || m_stack->m_owner == 3 )
      {
        r.drawTexturedQuad( data.x, data.y, 1, 1, "pirateNPC" );
      }
      else
      {
        r.drawTexturedQuad( data.x, data.y, 1, 1, "portNPC" );
      }     
      // Draw a pirate
    } 
    else if( m_stack->m_ports )
    {
      if( m_stack->m_owner == 0 )
      {
        r.drawTexturedQuad( data.x, data.y, 1, 1, "portGreen" );
      } 
      else if( m_stack->m_owner == 1 )
      {
        r.drawTexturedQuad( data.x, data.y, 1, 1, "portRed" );
      }
      else if( m_stack->m_owner == 2 || m_stack->m_owner == 3 )
      {
        r.drawTexturedQuad( data.x, data.y, 1, 1, "portNPC" );
      }
      else
      {
        r.drawTexturedQuad( data.x, data.y, 1, 1, "portNPC" );
      }
    }
    else if( m_stack->m_gold )
    {
      r.drawTexturedQuad( data.x, data.y, 1, 1, "treasure" );
    }

  }

}
