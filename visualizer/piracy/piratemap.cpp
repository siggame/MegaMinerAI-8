#include "piratemap.h"
#include <GL/gl.h>
#include <GL/glext.h>

#include <iostream>
#include <queue>
#include <math.h>
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

void PirateMap::blur( 
    int **map, 
    const int& width,
    const int& height,
    const int& radius,
    Orientation orient )
{  
  int x;
  int y;
  int i;
  int c;
  for( x = 0; x < width-1; x++ )
  {
    for( y = 0; y < height-1; y++ )
    {
      map[x][y] = 0;
      c = 0;

      switch( orient )
      {
        case horizontal:
          for( 
              i = ((x-radius) < 0 ? 0 : x-radius);
              i < ((x+radius+1) > width ? width : x+radius+1); 
              i++ )
          {
            map[x][y] += map[i][y+1];
            c++;
          }
          map[x][y] /= c;
          break;
        case vertical:
          for( 
              i = ((y-radius) < 0 ? 0 : y-radius);
              i < ((y+radius+1) > height ? height : y+radius+1); 
              i++ )
          {
            map[x][y] += map[x+1][i];
            c++;
          }
          map[x][y] /= c;
          break;
      }
    }
  }
}

void PirateMap::boxBlur( 
    int **map,
    const int& width,
    const int& height,
    const int& radius )
{
  blur( map, width, height, radius, horizontal );
  blur( map, width, height, radius, vertical );
}

#if 0
void PirateMap::findClosest( 
    int **map, 
    const int& width, 
    const int& height, 
    const int& xc, 
    const int& yc, 
    const int& rad )
{
  for( int x = xc-rad; x <= xc+rad; x++ )
  {
    for( int y = yc-rad; y <= yc+rad; y++ )
    {
      if( x == -rad || x == rad || y == -rad || y == rad )
      {
        if( x >= 0 && x < width && y >= 0 && y < height )
        {

        }
      } 
    }
  }
}
#endif

const int big = 30;

#define SQ(x) (x)*(x)

int PirateMap::distToTile( 
    const int& x, 
    const int& y, 
    const int& mapsize,
    const TileType& type, 
    const std::map<int, Tile>& tiles )
{
  int count = 0;

  double smallest = 9999;
  int ty;
  int tx;

  for( 
      std::map<int, Tile>::const_iterator i = tiles.begin();
      i != tiles.end();
      i++ )
  {

    if( 
        (type == land && i->second.type > 0)  || 
        (type == water && i->second.type <= 0)
      )
    {
      count++;
      int pusher = SQ(i->second.x-x) + SQ(i->second.y-y);
      if( pusher < smallest )
      {
        smallest = pusher;
        tx = i->second.x;
        ty = i->second.y;
      }

    }
  }

  cout << "Other: " << tx << ", " << ty << endl;

  return smallest;
}

void PirateMap::generateMap( Game& g )
{
  cout << "Generate Map: " << g.states[0].tiles.size() << endl;
  int pixels = 15;
  int mapSize = g.states[0].mapSize;
  int mWidth = mapSize*pixels;
  int mHeight = mapSize*pixels;

  int **depthMap = new int*[mWidth];
  int tx = 0;
  int ty = 0;

  for( int x = 0; x < mWidth; x++ )
  {
    depthMap[x] = new int[mHeight];
  }

#if 1 
  for( 
      std::map<int,Tile>::iterator i = g.states[0].tiles.begin();
      i != g.states[0].tiles.end();
      i++ )
  {
    ty = ((TileType)i->second.type == water ? -1 : 1);
    cout << "TYPE: " << i->second.type << endl;

    i->second.type = distToTile( 
        i->second.x, 
        i->second.y, 
        mapSize, 
        (TileType)(1-i->second.type),
        g.states[0].tiles ) * ty;
    cout << "Dist: " << i->second.type << endl;
  }
#endif

  for( int i = 0; i < g.states[0].tiles.size(); i++ )
  {
    for( int x = 0; x < pixels; x++ )
    {
      for( int y = 0; y < pixels; y++ )
      {
        tx = g.states[0].tiles[i].x;
        ty = g.states[0].tiles[i].y;
        
        depthMap[tx*pixels+x][ty*pixels+y] = g.states[0].tiles[i].type*big;

      }
    }
  }

  boxBlur( depthMap, mWidth, mHeight, pixels );

  int larger = 0;
  int smaller = 0;

#if 1
  for( int x = 0; x < mWidth; x++ )
  {
    for( int y = 0; y < mHeight; y++ )
    {
      larger = (depthMap[x][y] > larger) ? depthMap[x][y] : larger;
      smaller = (depthMap[x][y] < smaller) ? depthMap[x][y] : smaller;
    }
  }
#endif

#if 0
  for( int i = 0; i < g.states[0].tiles.size(); i++ )
  {
    larger = (g.states[0].tiles[i].type > larger ? g.states[0].tiles[i].type : larger);
    smaller = (g.states[0].tiles[i].type < smaller ? g.states[0].tiles[i].type : smaller);
  }
#endif

  bool neg = false;

  int t;

#if 1

  cout << "Larger: " << larger << endl;
  cout << "Smaller: " << smaller << endl;

  for( int x = 0; x < mWidth; x++ )
  {
    for( int y = 0; y < mHeight; y++ )
    {
      depthMap[x][y] = (depthMap[x][y] - larger) * 255 /(smaller-larger);
    }
  }
#endif

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
#if 1
  for( int x = 0; x < mWidth; x++ )
  {
    for( int y = 0; y < mHeight; y++ )
    {
      out.write( (const char*)&depthMap[x][y], 1 );
    }
  }
#endif
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
