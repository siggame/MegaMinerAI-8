#include "piraterender.h"
#include "piratedata.h"
#include <GL/gl.h>

PirateRender::PirateRender()
{
}

PirateRender::~PirateRender()
{
}

void PirateRender::update()
{

}

const GOC_IDType PirateRender::componentID() const
{
  return GOC_IDType( "GOCRenderPirate" );
}

void PirateRender::renderAt(
    const unsigned int& turn,
    const unsigned int& frame )
{
  if( getOwner() )
  {
    PirateData *d = ((PirateData*)getOwner()->getGOC( "DataFamily" ));
    if( d )
    {
      PirateDataInfo* t = d->getDataAt( turn, frame );
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
