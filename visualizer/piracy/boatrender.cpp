#include "boatrender.h"
#include "boatdata.h"
#include "GL/gl.h"

BoatRender::BoatRender()
{
}

BoatRender::~BoatRender()
{
}

void BoatRender::update()
{
}

const GOC_IDType BoatRender::componentID() const
{
  return GOC_IDType( "GOCRenderBoat" );
}
#include <iostream>
using namespace std;

void BoatRender::renderAt( 
    const unsigned int& turn,
    const unsigned int& frame )
{

  std::string goc = "GOC";
  if( getOwner() )
  {
    BoatDataInfo* t = ((BoatData*)getOwner()->getGOC( "GOCDataBoat" ))->getDataAt( turn, frame );

    if( t )
    {
      glPushMatrix();
      glTranslatef( t->x, t->y, 0 );

      glBegin( GL_QUADS );

      glVertex2f( 0, 0 );
      glVertex2f( 1, 0 );
      glVertex2f( 1, 1 );
      glVertex2f( 0, 1 );

      glEnd();

      glPopMatrix();
    }

  }

}

