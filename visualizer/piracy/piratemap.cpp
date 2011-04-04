#include "piratemap.h"
#include <GL/gl.h>

#include <iostream>
using namespace std;

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
  cout << "Generate Map: " << g.states[0].tiles.size() << endl;
  int pixels = 20;
  int mWidth = 40*pixels;
  int mHeight = 40*pixels;

  int **depthMap = new int*[mHeight];
  int tx = 0;
  int ty = 0;

  for( int x = 0; x < mWidth; x++ )
  {
    depthMap[x] = new int[mHeight];
  }

  for( int i = 0; i < g.states[0].tiles.size(); i++ )
  {
    for( int x = 0; x < pixels; x++ )
    {
      for( int y = 0; y < pixels; y++ )
      {
        tx = g.states[0].tiles[i].x;
        ty = g.states[0].tiles[i].y;
        depthMap[tx*pixels+x][ty*pixels+y] = g.states[0].tiles[i].type == 0 ? -99999 : 99999;
      }
    }
  }

  int larger = 0;
  int smaller = 0;
  int t;

  for( int y = mHeight-1; y >= 0; y-- )
  {
    for( int x = mWidth-1; x >= 0; x-- )
    {
      for( int s = 1; x+s < mWidth && y+s < mHeight; s++ )
      {
        if( x+s < mWidth )
        {

        } 

        if( y+s < mHeight )
        {

        }
      }
    }
  }

#if 0
  int mWidth = 40*20;
  int mHeight = 40*20;
  int nSize = mWidth*mHeight*3;
#endif
  //unsigned char *pixels = new unsigned char[nSize];
  std::ofstream out( "depth.tga" );

  unsigned char TGAheader[12] = {0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  unsigned char header[6] = {mWidth%256, mWidth/256, mHeight%256, mHeight/256, 8, 0 };

  out.write( (const char*)TGAheader, 12 );
  out.write( (const char*)header, 6 );
  for( int x = 0; x < mWidth; x++ )
  {
    out.write( (const char*)depthMap[x], mHeight );
  }
  //out.write( (const char*)pixels, nSize );


  out.close();


  for( int x = 0; x < mWidth; x++ )
  {
    delete [] depthMap[x];
  }

  delete [] depthMap;

#if 0
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  for( int i = 0; i < g.states[0].tiles.size(); i++ )
  {
    glPushMatrix();
#if 0
    switch( g.states[0].tiles[i].type )
    {
      case 0:
        glColor4f( 0, 0, 0, 1 );
        break;
      case 1:
        glColor4f( 1, 1, 1, 1 );
        break;
    }
#endif
    glColor4f( 1, 1, 1, 1 );
    glTranslatef( g.states[0].tiles[i].x, g.states[0].tiles[i].y, 0 );
    glScalef( 20, 20, 1 );
    glBegin( GL_QUADS );
    glVertex2f( 0, 0 );
    glVertex2f( 1, 0 );
    glVertex2f( 1, 1 );
    glVertex2f( 0, 1 );
    glEnd();
    glPopMatrix();
  }
  glReadBuffer( GL_BACK );
  drawTGA( "output.tga" );
#endif
}

void PirateMap::drawTGA( std::string filename )
{
  int mWidth = 40*20;
  int mHeight = 40*20;
  int nSize = mWidth*mHeight*3;
  unsigned char *pixels = new unsigned char[nSize];
  std::ofstream out( filename.c_str() );

  glPixelStorei( GL_PACK_ALIGNMENT, 1 );
  glPixelStorei( GL_PACK_IMAGE_HEIGHT, mWidth );
  glPixelStorei( GL_PACK_ROW_LENGTH, mHeight );

  glReadPixels( 0, 0, mWidth, mHeight, GL_BGR, GL_UNSIGNED_BYTE, pixels );

  unsigned char TGAheader[12] = {0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  unsigned char header[6] = {mWidth%256, mWidth/256, mHeight%256, mHeight/256, 24, 0 };

  out.write( (const char*)TGAheader, 12 );
  out.write( (const char*)header, 6 );
  out.write( (const char*)pixels, nSize );

  delete [] pixels;

  out.close();

}

void PirateMap::renderAt(
    const unsigned int& turn,
    const unsigned int& frame
    )
{
  glPushMatrix();

  glPopMatrix();
}
