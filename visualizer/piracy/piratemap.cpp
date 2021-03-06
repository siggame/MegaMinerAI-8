#include "piratemap.h"
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glu.h>
#include <iostream>
#include <queue>
#include <cmath>
using namespace std;

namespace visualizer
{

  const int powers[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8182, 16384, 32728, 65536 };
  void PirateMap::generateMap( Game& g, IGame& intf )
  {
    int pixels = intf.options->getInt( "unitSize" );
    int mapSize = g.states[0].mapSize;
    int mWidth = mapSize*pixels;
    int mHeight = mapSize*pixels;
    mapW = mapH = mapSize;
    Renderer = intf.renderer;

    int **depthMap = new int*[mWidth];
    int tx = 0;
    int ty = 0;

    // Set the depthmap to sealevel
    for( int x = 0; x < mWidth; x++ )
    {
      depthMap[x] = new int[mHeight];
      memset( depthMap[x], 0, sizeof( int ) * mHeight );
    }

    const int big = 50;
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

      for( int x = 0; x < (int)pixels; x++ )
      {
        for( int y = 0; y < (int)pixels; y++ )
        {
          tx = i->second.x;
          ty = i->second.y;

          depthMap
            [(int)((float)(tx)*pixels)+x]
            [(int)((float)(ty)*pixels)+y]
            = i->second.type*big;

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

    boxBlur( depthMap, mWidth, mHeight, intf.options->getInt( "blurRadius" ) );

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


    const QImage& i1 = ((ResTexture*)intf.resourceManager->reference( "proc1", "pirateMap" ))->getQImage();
    const QImage& i2 = ((ResTexture*)intf.resourceManager->reference( "proc2", "pirateMap" ))->getQImage();
    const QImage& i4 = ((ResTexture*)intf.resourceManager->reference( "proc4", "pirateMap" ))->getQImage();
    const QImage& i5 = ((ResTexture*)intf.resourceManager->reference( "proc5", "pirateMap" ))->getQImage();
    const QImage& i6 = ((ResTexture*)intf.resourceManager->reference( "proc6", "pirateMap" ))->getQImage();
    const QImage& i9 = ((ResTexture*)intf.resourceManager->reference( "proc9", "pirateMap" ))->getQImage();
    QImage textures[10] =
      {
        i1,
        i2,
        i2,
        i4,
        i5,
        i6,
        i6,
        i6,
        i9,
        i9
      };

    intf.resourceManager->release( "proc1", "pirateMap" );
    intf.resourceManager->release( "proc2", "pirateMap" );
    intf.resourceManager->release( "proc4", "pirateMap" );
    intf.resourceManager->release( "proc5", "pirateMap" );
    intf.resourceManager->release( "proc6", "pirateMap" );
    intf.resourceManager->release( "proc9", "pirateMap" );


    int depths[10] =
    {
      intf.options->getInt( "depth1" ),
      intf.options->getInt( "depth2" ),
      intf.options->getInt( "depth3" ),
      intf.options->getInt( "depth4" ),
      intf.options->getInt( "depth5" ),
      intf.options->getInt( "depth6" ),
      intf.options->getInt( "depth7" ),
      intf.options->getInt( "depth8" ),
      intf.options->getInt( "depth9" ),
      intf.options->getInt( "depth10" )
    };

    QImage result( mWidth, mHeight, QImage::Format_RGB32 );

    for( int x = 0; x < mWidth; x++ )
    {
      for( int y = 0; y < mHeight; y++ )
      {
        result.setPixel( x, y, interpolate( x, y, 10, textures, depths, depthMap[x][y] ) );
      }
    }

    intf.resourceManager->loadTexture( result, "mapTexture" );

    for( int x = 0; x < mWidth; x++ )
    {
      delete [] depthMap[x];
    }

    delete [] depthMap;

  } // PirateMap::GenerateMap()


  int PirateMap::distToTile
    (
    const int& x,
    const int& y,
    const int& /*mapsize*/,
    const TileType& type,
    const std::map<int, Tile>& tiles 
    )
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
        int pusher = abs(i->second.x-x) + abs(i->second.y-y);
        if( pusher < smallest )
        {
          smallest = pusher;
          tx = i->second.x;
          ty = i->second.y;
        }

      }
    }

    return smallest;
  } // PirateMap::distToTile()


  void PirateMap::boxBlur
    (
    int **map,
    const int& width,
    const int& height,
    const int& radius 
    )
  {

    float *gaussian = new float[radius*2+1];
    //float sigma = OptionsMan->getFloat( "sigma" );

    #if 0
    for( int i = -radius; i < radius+1; i++ )
    {
      gaussian[i+radius] = (exp( -(i*i)/(2*sigma*sigma ) )/(2*PI*sigma*sigma));
      gaussian[i+radius] = (float)1/11;
      cout << gaussian[i+radius] << ", " << endl;
      //cout << (2*PI*sigma*sigma) << endl;
    }
    #endif

    #if 1
    blur( map, width, height, radius, gaussian, horizontal );
    blur( map, width, height, radius, gaussian, vertical );
    #endif

    delete [] gaussian;

  } // PirateMap::boxBlur()

  void PirateMap::blur
    (
    int **map,
    const int& width,
    const int& height,
    const int& radius,
    const float* /*gaussian*/,
    Orientation orient 
    )
  {
    int x;
    int y;
    int i;
    int c;
    int index;
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
              index = i-x+radius;

            #if 0
              if(
                (map[x][y+1] > 0 && map[i][y+1] > 0) ||
                (map[x][y+1] <= 0 && map[i][y+1] <= 0)
                )
            #endif
              {
                map[x][y] += map[i][y+1];
                c++;
              }
            }
            map[x][y] /= c;
          #if 0
            if( map[x][y+1] > 0 && map[x][y] < 0 )
            {
              map[x][y] = 0;
            } else if( map[x][y+1] < 0 && map[x][y] > 0 )
            {
              map[x][y] = 0;
            }
            else
            {
              if( c > 0 )
                map[x][y] /= c;
            }
          #endif
            break;
          case vertical:
            for(
              i = ((y-radius) < 0 ? 0 : y-radius);
              i < ((y+radius+1) > height ? height : y+radius+1);
              i++ )
            {
              index = i-x+radius;
            #if 0
              if(
                (map[x+1][y] > 0 && map[x+1][i] > 0) ||
                (map[x+1][y] <= 0 && map[x+1][i] <= 0 )
                )
            #endif
              {
                map[x][y] += map[x+1][i];
                c++;
              }
            }
            map[x][y] /= c;

          #if 0
            if( map[x+1][y] > 0 && map[x][y] < 0 )
            {
              map[x][y] = 0;
            } else if( map[x+1][y] < 0 && map[x][y] > 0 )
            {
              map[x][y] = 0;
            }
            else
            {
              map[x][y] /= c;
            }
          #endif
            break;
        }
      }
    }

  } // PirateMap::blur()


  QRgb PirateMap::interpolate( int x, int y, int size, QImage *images, int *depths, int depth )
  {

    if (!images || !depths)
      return QRgb();

    int i;
    for( i = 0; i < size; i++ )
    {
      if( depth <= depths[i] )
      {
        break;
      }
    }

    --i;
    //std::cout << "i " << i << '\n';

    float r0, g0, b0;
    float r1, g1, b1;


    #if 0
    r0 = qRed( images[i].pixel( x, y ) );
    g0= qGreen( images[i].pixel( x, y ) );
    b0= qBlue( images[i].pixel( x, y ) );
    r1 = qRed(  images[i+1].pixel( x, y ) );
    g1 = qGreen(  images[i+1].pixel( x,y ) );
    b1 = qBlue(  images[i+1].pixel( x, y ) );
#else

    QRgb c0 = ((QRgb*)images[i].scanLine(y))[x];
    QRgb c1 = ((QRgb*)images[i+1].scanLine(y))[x];
    #endif

#if 0
    QRgb color = qRgb(
      (int)interp( depth, depths[i], depths[i+1], b0, b1 ),
      (int)interp( depth, depths[i], depths[i+1], g0, g1 ),
      (int)interp( depth, depths[i], depths[i+1], r0, r1 ) );
#else
    QRgb color = qRgb(
      (int)interp( depth, depths[i], depths[i+1], qBlue( c0 ), qBlue( c1 ) ),
      (int)interp( depth, depths[i], depths[i+1], qGreen( c0 ), qGreen( c1 )),
      (int)interp( depth, depths[i], depths[i+1], qRed( c0 ) , qRed( c1 ) ) );

#endif

    return color;

  } // PirateMap::interpolate()


  float PirateMap::interp( float x,  float x0, float x1, float y0, float y1  )
  {

    return y0 + (x-x0)*((y1-y0)/(x1-x0));

  } // PirateMap::interp()



#if 0
  PirateMap::PirateMap()
  {
  }


  PirateMap::~PirateMap()
  {
  }

#define PI 3.1415926535897932384626433832795028841971

  unsigned char **images;

#if 1
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
#endif


  void PirateMap::renderAt(
  const unsigned int& /*turn*/,
  const unsigned int&	/*frame*/
  )
  {
    glPushMatrix();

    glEnable( GL_TEXTURE );
    glEnable( GL_TEXTURE_2D );

    glColor4f( 1, 1, 1, 1 );

    static bool first = true;
    static ResTexture res;
    if( first )
    {
      first = false;
      res.load( "./piracy/textures/font1.png" );
    }

    glBindTexture( GL_TEXTURE_2D, mapTexture.getTexture() );

    const float tex = 1-((float)m_width/m_power);
    glBegin( GL_QUADS );

    glTexCoord2f( 0, 1);
    glVertex3f( 0, 0, 0 );

    glTexCoord2f( 1-tex, 1);
    glVertex3f( Renderer->height(), 0, 0 );

    glTexCoord2f( 1-tex, tex );
    glVertex3f( Renderer->height(), Renderer->height(), 0 );

    glTexCoord2f( 0, tex );
    glVertex3f( 1, Renderer->height(), 0 );
    glEnd();

    glDisable( GL_BLEND);
    glDisable( GL_TEXTURE );
    glDisable( GL_TEXTURE_2D );

    #if 0
    glColor4f( 1, 1, 1, 1 );

    glTranslatef( -2, 2, 0 );

    float size = ((float)Renderer<DupObj>::height())/OptionsMan->getInt("mapSize");
    for( int i = 0; i < 41; i++ )
    {
      glBegin( GL_QUADS );
      glVertex3f( 0, 0, -2 );
      glVertex3f( size, 0, -2 );
      glVertex3f( size, size, -2 );
      glVertex3f( 0, size, -2 );
      glEnd();
      glTranslatef( size, size, 0 );
    }
    #endif

    glPopMatrix();
  }
#endif
  
} // visualizer
