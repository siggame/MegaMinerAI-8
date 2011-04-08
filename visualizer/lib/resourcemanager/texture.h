#ifndef RESTEXTURE_H
#define RESTEXTURE_H

#include "resource.h"
#include <QImage>
#include <QPainter>
#include <QString>


class ResTexture : public Resource
{
	private:
		QImage texture;
		unsigned int texId;
	public:
		bool load( const std::string & path );
		ResTexture():Resource(RT_TEXTURE){}
		ResTexture(const std::string & path):Resource(RT_TEXTURE){load(path);}

		int getWidth()
		{
			return texture.width();
		}

		int getHeight()
		{
			return texture.height();
		}

		int getTexture()
		{
			return texId;
		}
};


#endif
