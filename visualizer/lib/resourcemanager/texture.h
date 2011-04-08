#ifndef RESTEXTURE_H
#define RESTEXTURE_H

#include "resource.h"
#include <QImage>
#include <QString>


class ResTexture : public Resource
{
	private:
		QImage texture;
		unsigned int texId;
	public:
		bool loadImage( const QString & path );

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
