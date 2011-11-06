#include "common.h"
#include "textureloader.h"
#include <cmath>

#include <qgl.h>

namespace visualizer
{

  _TextureLoader *TextureLoader = 0;

  IMAGE_TYPE getImageType(const QString& path)
  {
    if ( path.endsWith(".tif"))
      return IMG_TIFF;
    if ( path.endsWith(".png"))
      return IMG_PNG;
    if ( path.endsWith(".tga"))
      return IMG_TGA;
    if ( path.endsWith(".bmp"))
      return IMG_BMP;

    return IMG_NONE;
  } // _TextureLoader::getImageType()

  int _TextureLoader::load( const std::string& path, QImage& texture )
  {
    unsigned int texId;
    glEnable( GL_TEXTURE_2D );

    switch( getImageType( path.c_str() ) )
    {
      case IMG_TIFF:
        loadGeneric( path.c_str(), texId, texture );
        break;
      case IMG_PNG:
        loadGeneric( path.c_str(), texId, texture );
        break;
      case IMG_TGA:
        loadGeneric( path.c_str(), texId, texture );
        break;
      case IMG_BMP:
        loadGeneric( path.c_str(), texId, texture );
        break;
      default:
        THROW 
          (
          Exception, 
          "Image Type Unknown\n Texture: %s",
          path.c_str()
          );
    }

    glDisable( GL_TEXTURE_2D );
    return texId;

  } // _TextureLoader::load()

  unsigned int powers[] = { 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8182, 16384 };

  void _TextureLoader::loadGeneric(const std::string& path, unsigned int & texId, QImage & texture)
  {
    QImage buffer;

    if (!buffer.load( path.c_str() ))
    {
      THROW
        (
        Exception,
        "Could Not Load Texture.\n Path: %s",
        path.c_str()
        );
    }

    size_t width = powers[ (size_t)log2( buffer.width()-1 )  ];
    size_t height = powers[ (size_t)log2( buffer.height()-1 ) ];

    QImage fixed( width, height, QImage::Format_ARGB32 );
#if __DEBUG__
    cout << path << endl;
    cout << "w: " << width << " h: " << height << endl;
#endif
    QPainter painter(&fixed);

    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect( fixed.rect(), Qt::transparent );
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawImage( 0, 0, buffer );
    painter.end();

    texture = QGLWidget::convertToGLFormat( fixed.mirrored( true, false ) );

    glGenTextures( 1, &texId );
    if( texId == 0 )
    {
      THROW
        (
        Exception,
        "OpenGL Rendering Context Not Valid.  This is Causing glGenTextures to return 0."
        );
    }

    glBindTexture( GL_TEXTURE_2D, texId );

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );

    gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGBA, texture.width(), texture.height(), GL_RGBA, GL_UNSIGNED_BYTE, texture.bits() );

  } // _TextureLoader::loadPNG()

  void _TextureLoader::loadQImage( unsigned int& texId, QImage& texture )
  {

    size_t tempW, tempH;
    for( tempW = 0; tempW < sizeof( powers )/sizeof(unsigned int); tempW++ )
    {
      if( texture.width() <= powers[tempW] )
        break;
    }

    for( tempH = 0; tempH < sizeof( powers )/sizeof(unsigned int); tempH++ )
    {
      if( texture.height() <= powers[tempH] )
        break;
    }

    QImage fixed( powers[tempW], powers[tempH], QImage::Format_ARGB32 );
    QPainter painter(&fixed);

    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect( fixed.rect(), Qt::transparent );
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    QRectF t( 0, 0, powers[tempW], powers[tempH] );
    QRectF s( 0, 0, texture.width(), texture.height() );
    painter.drawImage( t, texture, s );
    painter.end();

    texture = QGLWidget::convertToGLFormat( fixed.mirrored( true, false ) );


    glGenTextures( 1, &texId );

    GLenum errCode; 
    const GLubyte *errString; 

    if ((errCode = glGetError()) != GL_NO_ERROR) 
    { 
      errString = gluErrorString(errCode); 
      fprintf (stderr, "OpenGL Error: %s\n", errString); 
    } 

    if( texId == 0 )
    {
      THROW
        (
        Exception,
        "glGenTextures returned a texture id of 0.  This typically means the OpenGL Rendering Context Not Valid. Make sure you're not running this function from a separate thread."
        );
    }

    glBindTexture( GL_TEXTURE_2D, texId );
    //glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );

    gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGBA, texture.width(), texture.height(), GL_RGBA, GL_UNSIGNED_BYTE, texture.bits() );


  } // _TextureLoader::loadQImage()

  void _TextureLoader::setup()
  {
    if( !TextureLoader )
    {
      TextureLoader = new _TextureLoader;
    }
    else
    {
      THROW
      (
      Exception,
      "Texture Loader is already initialized."
      );
    }
  } // _TextureLoader::setup()

  void _TextureLoader::destroy()
  {
    delete TextureLoader;
    TextureLoader = 0;
  } // _TextureLoader::destroy()

} // visualizer

