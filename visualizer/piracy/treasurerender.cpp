#include "treasurerender.h"
#include "treasuredata.h"
#include <GL/gl.h>
#include <iostream>
using namespace std;

TreasureRender::TreasureRender()
{
}

TreasureRender::~TreasureRender()
{
}

void TreasureRender::update()
{

}

const GOC_IDType TreasureRender::componentID() const
{
  return GOC_IDType( "GOCRenderTreasure" );
}

void TreasureRender::renderAt(
    const unsigned int& turn,
    const unsigned int& frame )
{
  if( getOwner() )
  {
    TreasureData *d = ((TreasureData*)getOwner()->getGOC( "DataFamily" ));
    if( d )
    {
      TreasureDataInfo* t = d->getData();
      if( t )
      {
        //cout << "X: " << t->x << ", Y: " << t->y << endl;
        glEnable( GL_BLEND );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
        glPushMatrix();
        glTranslatef( t->x, t->y, 0 );
        glColor4f( 0, 1, 0, 0.25 );
        glBegin( GL_QUADS );
        glVertex3f( 0, 0, -2 );
        glVertex3f( 1, 0, -2 );
        glVertex3f( 1, 1, -2 );
        glVertex3f( 0, 1, -2 );
        glEnd();
        glPopMatrix();
      }
    }
  }
}
