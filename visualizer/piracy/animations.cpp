#include "animations.h"

namespace visualizer
{

// A Macros may be useful for c++ shadows a parameterthis.  I dunno.
  void StartAnim::animate( float t, AnimData *d )
  {
    PirateData& data = ((PirateData&)*d);

  }

  void LeftAnim::animate( float t, AnimData *d )
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

  void RightAnim::animate( float t, AnimData *d )
  {
    PirateData& data = ((PirateData&)*d);
  }

  void UpAnim::animate( float t, AnimData *d )
  {
    PirateData& data = ((PirateData&)*d);
  }

  void DownAnim::animate( float t, AnimData *d )
  {
    PirateData& data = ((PirateData&)*d);
  }

  void AttackAnim::animate( float t, AnimData *d )
  {
    PirateData& data = ((PirateData&)*d);
  }

  void TalkAnim::animate( float t, AnimData *d )
  {
    PirateData& data = ((PirateData&)*d);
  }

  void DrawStack::animate( float t, AnimData *d )
  {
    PirateData& data = ((PirateData&)*d);
  }

} // visualizer
