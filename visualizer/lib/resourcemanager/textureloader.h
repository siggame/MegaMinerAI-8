#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

namespace visualizer
{

enum IMAGE_TYPE
{
  IMG_NONE, IMG_TIFF, IMG_PNG, IMG_TGA, IMG_BMP
};

IMAGE_TYPE getImageType(const QString & path)
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
}


class _TextureLoader: public Module, public ITextureLoader
{
  Q_INTERFACES( ITextureLoader );
  public:

};

}


#endif
