#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include "itextureloader.h"
#include <QtPlugin>
#include <QImage>
#include <QString>

namespace visualizer
{

  enum IMAGE_TYPE
  {
    IMG_NONE, IMG_TIFF, IMG_PNG, IMG_TGA, IMG_BMP
  };

  class _TextureLoader: public Module, public ITextureLoader
  {
    
    Q_INTERFACES( ITextureLoader );
    public:

    int load( const std::string& path, QImage& texture );
    void loadGeneric( const std::string& path, unsigned int& texId, QImage& texture );
    void loadQImage( unsigned int& texId, QImage& texture );

    static void setup();
    static void destroy();



  };

  extern _TextureLoader *TextureLoader;

}


#endif
