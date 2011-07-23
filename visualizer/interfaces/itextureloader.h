#ifndef ITEXTURELOADER_H
#define ITEXTURELOADER_H

#include <QImage>

class ITextureLoader
{
public:
  virtual int load( const std::string& path, QImage& texture ) = 0;

};

#endif
