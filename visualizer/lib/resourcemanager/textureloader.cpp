#include "common.h"
#include "textureloader.h"

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
        loadTIFF( path.c_str(), texId, texture );
        break;
      case IMG_PNG:
        loadPNG( path.c_str(), texId, texture );
        break;
      case IMG_TGA:
        loadTGA( path.c_str(), texId, texture );
        break;
      case IMG_BMP:
        loadBMP( path.c_str(), texId, texture );
        break;
      default:
        THROW 
          (
          Exception, 
          "Image Type Unknown\n Texture: %s",
          path.c_str()
          );
    }
    return texId;

  } // _TextureLoader::load()

  void _TextureLoader::loadTIFF(const std::string& path, unsigned int & texId, QImage & texture)
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

    QImage fixed( buffer.width(), buffer.height(), QImage::Format_ARGB32 );
    QPainter painter( &fixed );

    painter.setCompositionMode( QPainter::CompositionMode_Source );
    painter.fillRect( fixed.rect(), Qt::transparent );
    painter.setCompositionMode( QPainter::CompositionMode_SourceOver );
    painter.drawImage( 0, 0, buffer );
    painter.end();

    texture = QGLWidget::convertToGLFormat( fixed );
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
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

    glTexImage2D
      ( 
      GL_TEXTURE_2D, 
      0, 
      4, 
      texture.width(), 
      texture.height(), 
      0, 
      GL_RGBA, 
      GL_UNSIGNED_BYTE, 
      texture.bits() 
      );
      
    //gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGBA, texture.width(),texture.height(), GL_RGBA, GL_UNSIGNED_BYTE, texture.bits() );

  } // _TextureLoader::loadTIFF()


  void _TextureLoader::loadPNG(const std::string& path, unsigned int & texId, QImage & texture)
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

    QImage fixed( buffer.width(), buffer.height(), QImage::Format_ARGB32 );
    cout << path << endl;
    cout << "w: " << buffer.width() << " h: " << buffer.height() << endl;
    QPainter painter(&fixed);

    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect( fixed.rect(), Qt::transparent );
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawImage( 0, 0, buffer );
    painter.end();

    texture = QGLWidget::convertToGLFormat( fixed );

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
    //glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );

#if 0
    glTexImage2D
      ( 
      GL_TEXTURE_2D,
      0,
      4,
      texture.width(),
      texture.height(),
      0,
      GL_RGBA,
      GL_UNSIGNED_BYTE,
      texture.bits() 
      );
#endif
    gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGBA, texture.width(), texture.height(), GL_RGBA, GL_UNSIGNED_BYTE, texture.bits() );

  } // _TextureLoader::loadPNG()

  void _TextureLoader::loadTGA(const std::string& path, unsigned int & texId, QImage & texture)
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

    QImage fixed( buffer.width(), buffer.height(), QImage::Format_ARGB32 );
    QPainter painter(&fixed);

    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect( fixed.rect(), Qt::transparent );
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawImage( 0, 0, buffer );
    painter.end();

    texture = QGLWidget::convertToGLFormat( fixed );
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
    //	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D
      ( 
      GL_TEXTURE_2D,
      0,
      4,
      texture.width(),
      texture.height(),
      0,
      GL_RGBA,
      GL_UNSIGNED_BYTE,
      texture.bits() 
      );
    //gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGBA, texture.width(),texture.height(), GL_RGBA, GL_UNSIGNED_BYTE, texture.bits() );

  } // _TextureLoader::loadTGA()


  void _TextureLoader::loadBMP(const std::string& path, unsigned int & texId, QImage & texture)
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

    QImage fixed( buffer.width(), buffer.height(), QImage::Format_ARGB32 );
    QPainter painter( &fixed );

    painter.setCompositionMode( QPainter::CompositionMode_Source );
    painter.fillRect( fixed.rect(), Qt::transparent );
    painter.setCompositionMode( QPainter::CompositionMode_SourceOver );
    painter.drawImage( 0, 0, buffer );
    painter.end();

    texture = QGLWidget::convertToGLFormat( fixed );
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
    //	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

    glTexImage2D
      ( 
      GL_TEXTURE_2D, 
      0, 
      4, 
      texture.width(), 
      texture.height(), 
      0, 
      GL_RGBA, 
      GL_UNSIGNED_BYTE, 
      texture.bits() 
      );
    //gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGBA, texture.width(),texture.height(), GL_RGBA, GL_UNSIGNED_BYTE, texture.bits() );

  } // _TextureLoader::loadBMP()

  void _TextureLoader::loadQImage( unsigned int& texId, QImage& texture )
  {
    glEnable( GL_TEXTURE_2D );

    QImage fixed( texture.width(), texture.height(), QImage::Format_ARGB32 );
    QPainter painter(&fixed);

    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect( fixed.rect(), Qt::transparent );
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawImage( 0, 0, texture );
    painter.end();

    texture = QGLWidget::convertToGLFormat( fixed );


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

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );

#if 0
    glTexImage2D
      ( 
      GL_TEXTURE_2D,
      0,
      4,
      texture.width(),
      texture.height(),
      0,
      GL_RGBA,
      GL_UNSIGNED_BYTE,
      texture.bits() 
      );
#endif
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

