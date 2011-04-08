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
		bool loadImage( QString path );

		int getWidth();
		int getHeight();

		int getTexture();
};


#endif
