#include "piratemap.h"
#include <GL/gl.h>

PirateMap::PirateMap()
{
}

PirateMap::~PirateMap()
{
}

const GOC_IDType PirateMap::componentID() const
{
  return GOC_IDType( "GOCPirateMap" );
}

void PirateMap::update()
{

}

void PirateMap::generateMap( Game& g )
{
}

void PirateMap::renderAt(
    const unsigned int& turn,
    const unsigned int& frame
    )
{
  glPushMatrix();

  glPopMatrix();
}
