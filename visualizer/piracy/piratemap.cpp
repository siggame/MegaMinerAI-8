#include "piratemap.h"
#include <GL/gl.h>
#include <GL/glext.h>

#include "../lib/optionsmanager/optionsman.h"
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
#if 0
          if( map[x][y+1] > 0 && map[x][y] < 0 )
          {
            map[x][y] = 0;
          } else if( map[x][y+1] < 0 && map[x][y] > 0 )
          {
            map[x][y] = 0;
          } else {
            map[x][y] /= c;
          }
#endif
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

#if 0
          if( map[x+1][y] > 0 && map[x][y] < 0 )
          {
            map[x][y] = 0;
          } else if( map[x+1][y] < 0 && map[x][y] > 0 )
          {
            map[x][y] = 0;
          } else {
            map[x][y] /= c;
          }
#endif
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

  return smallest;
}

float PirateMap::interp( float x,  float x0, float x1, float y0, float y1  )
{

  return y0 + (x-x0)*((y1-y0)/(x1-x0));

}

QRgb PirateMap::interpolate( int x, int y, int size, QImage *images, int *depths, int depth )
{
  int i;
  for( i = 0; i < size; i++ )
  {
    if( depth <  depths[i] )
    {
      break;
    }
  }

  --i;

  float r0, g0, b0;
  r0 = qRed( images[i].pixel( x, y ) );
  g0= qGreen( images[i].pixel( x, y ) );
  b0= qBlue( images[i].pixel( x, y ) );
  float r1, g1, b1;
  r1 = qRed(  images[i+1].pixel( x, y ) );
  g1 = qGreen(  images[i+1].pixel( x,y ) );
  b1 = qBlue(  images[i+1].pixel( x, y ) );


  QRgb color = qRgb( 
      (int)interp( depth, depths[i], depths[i+1], b0, b1 ),
      (int)interp( depth, depths[i], depths[i+1], g0, g1 ),
      (int)interp( depth, depths[i], depths[i+1], r0, r1 ) );
  
#if 0
  if( depth > 150 )
    cout << i << ": " << depths[i] << ", " << depth << ", " << depths[i+1] << endl;
#endif

  return color;

}

void PirateMap::generateMap( Game& g )
{
  cout << "Generate Map: " << g.states[0].tiles.size() << endl;
  int pixels = 15;
  int mapSize = g.states[0].mapSize;
  int mWidth = 1024; //mapSize*pixels;
  int mHeight = 1024; //mapSize*pixels;
  pixels = 1024/mapSize;

  int **depthMap = new int*[mWidth];
  int tx = 0;
  int ty = 0;

  for( int x = 0; x < mWidth; x++ )
  {
    depthMap[x] = new int[mHeight];
    memset( depthMap[x], 0, sizeof( int ) * mHeight );
  }

  for( 
      std::map<int,Tile>::iterator i = g.states[0].tiles.begin();
      i != g.states[0].tiles.end();
      i++ )
  {
    ty = ((TileType)i->second.type == water ? -1 : 1);

    i->second.type = distToTile( 
        i->second.x, 
        i->second.y, 
        mapSize, 
        (TileType)(1-i->second.type),
        g.states[0].tiles ) * ty;
  }

  const int big = 100;
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

  int larger = 0;
  int smaller = 0;

  for( int x = 0; x < mWidth; x++ )
  {
    for( int y = 0; y < mHeight; y++ )
    {
      larger = (depthMap[x][y] > larger) ? depthMap[x][y] : larger;
      smaller = (depthMap[x][y] < smaller) ? depthMap[x][y] : smaller;
    }
  }

  boxBlur( depthMap, mWidth, mHeight, optionsMan::getInt( "blurRadius" ) );

  for( int x = 0; x < mWidth; x++ )
  {
    for( int y = 0; y < mHeight; y++ )
    {
      if( depthMap[x][y] > 0 )
      {
        depthMap[x][y] = (depthMap[x][y]*127)/larger;
      } else
      {
        depthMap[x][y] = -(depthMap[x][y]*127)/smaller;
      }

      depthMap[x][y] += 127;
      depthMap[x][y] = 255-depthMap[x][y];
    }
  }

  ResTexture r;

  QImage textures[10];
  std::string textureNames[10] = 
  {
    optionsMan::getStr( "proc1" ),
    optionsMan::getStr( "proc2" ),
    optionsMan::getStr( "proc3" ),
    optionsMan::getStr( "proc4" ),
    optionsMan::getStr( "proc5" ),
    optionsMan::getStr( "proc6" ),
    optionsMan::getStr( "proc7" ),
    optionsMan::getStr( "proc8" ),
    optionsMan::getStr( "proc9" ),
    optionsMan::getStr( "proc10" )
  };
  int depths[10] = {
    optionsMan::getInt( "depth1" ),
    optionsMan::getInt( "depth2" ),
    optionsMan::getInt( "depth3" ),
    optionsMan::getInt( "depth4" ),
    optionsMan::getInt( "depth5" ),
    optionsMan::getInt( "depth6" ),
    optionsMan::getInt( "depth7" ),
    optionsMan::getInt( "depth8" ),
    optionsMan::getInt( "depth9" ),
    optionsMan::getInt( "depth10" )
  };

  for( int i = 0; i < 10; i++ )
  {
    r.load( textureNames[i] );
    textures[i] = r.getQImage();
  }


  QImage result( mWidth, mHeight, QImage::Format_RGB32 );

  for( int x = 0; x < mWidth; x++ )
  {
    for( int y = 0; y < mHeight; y++ )
    {
      //result.setPixel( x, y, qRgb( depthMap[x][y], depthMap[x][y], depthMap[x][y] ) );
      
      //result.setPixel( x, y, textures[0].pixel( x, y ) );
      result.setPixel( x, y, interpolate( x, y, 10, textures, depths, depthMap[x][y] ) );
    }
  }

  result.save( "output.png", "PNG" );

#if 1
  std::ofstream out( "depth.tga" );

  unsigned char TGAheader[12] = {0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  unsigned char header[6] = {mWidth%256, mWidth/256, mHeight%256, mHeight/256, 8, 0 };

  out.write( (const char*)TGAheader, 12 );
  out.write( (const char*)header, 6 );

  for( int x = 0; x < mWidth; x++ )
  {
    for( int y = 0; y < mHeight; y++ )
    {
      out.write( (const char*)&depthMap[x][y], 1 );
    }
  }

  out.close();
#endif

  for( int x = 0; x < mWidth; x++ )
  {
    delete [] depthMap[x];
  }

  delete [] depthMap;

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
