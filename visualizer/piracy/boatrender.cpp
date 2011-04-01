#include "boatrender.h"
#include "boatdata.h"
#include <GL/gl.h>

// DEBUG LIBS
#include <iostream>
#include <string>
using namespace std;


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
        glColor4f( 0, 0, 1, 0.01 );
        glPushMatrix();
        glTranslatef( t->x, t->y, 0 );

        glBegin( GL_QUADS );

        glVertex3f( 0, 0, -1 );
        glVertex3f( 1, 0, -1 );
        glVertex3f( 1, 1, -1 );
        glVertex3f( 0, 1, -1 );

        glEnd();

        glPopMatrix();
      }
    }

  }

}

