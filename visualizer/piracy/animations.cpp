#include "animations.h"

namespace visualizer
{

// A Macros may be useful for c++ shadows a parameterthis.  I dunno.
  void StartAnim::animate( const float& t, AnimData *d )
  {
    PirateData& data = ((PirateData&)*d);
    data.x = m_stack->m_x;
    data.y = m_stack->m_y;

  }

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
  }

  void UpAnim::animate( const float& t, AnimData *d )
  {
    PirateData& data = ((PirateData&)*d);
  }

  void DownAnim::animate( const float& t, AnimData *d )
  {
    PirateData& data = ((PirateData&)*d);
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

    r.setColor( 1, 0, 0, 1 );

#if 0
    cout << endl 
      << "X: " << data.x  << " Y: " << data.y << endl;
 
#endif
    r.drawQuad( data.x*10, data.y*10, 10, 10 );
    r.drawQuad( data.x, data.y, 1, 1 );

    if( m_stack->m_ships )
    {
      if( m_stack->m_pirates )
      {
        // Draw Pirate On Top
        
      }
      // Draw Ship

#if 0
      cout << "Pirates: " << endl;
      for
        ( 
        std::vector<int>::iterator i = m_stack->m_pirateIds.begin();
        i != m_stack->m_pirateIds.end();
        i++ 
        )
      {
        cout << *i << ", ";
      }

      cout << endl 
        << "X: " << data.x  << " Y: " << data.y << endl;
#endif
    }
    else if( m_stack->m_pirates )
    {
      // Draw a pirate
      cout << "pirate" << endl;
    }


  }

}
