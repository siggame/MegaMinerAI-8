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
#include <string>
using namespace std;

void BoatRender::renderAt( 
    const unsigned int& turn,
    const unsigned int& frame )
{

  if( getOwner() )
  {
    BoatData *d = ((BoatData*)getOwner()->getGOC( "DataFamily" ));
    if( d )
    {
      BoatDataInfo* t = d->getDataAt( turn, frame );
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

}

