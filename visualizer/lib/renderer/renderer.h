#ifndef RENDERER_H
#define RENDERER_H

#include "../singleton.h"
#include <map>
#include <GL/gl.h>
//#include "drawGLFont.h"
#include "../optionsmanager/optionsman.h"
#include "../gocfamily_render.h"

//this is a place holder
typedef  GOCFamily_Render renderObj;

#define renderHeightName "renderHeight"
#define renderWidthName "renderWidth"
#define renderDepthName "renderDepth"

class Renderer : public Singleton<Renderer>
{
	public:
		static bool reg(const unsigned int & id, renderObj * obj);
		static bool del(const unsigned int & id);

		static bool setup(/**@todo make options*/);
		static bool clear();

		static renderObj * getRenderObject(const unsigned int id);

		static bool create(/**@todo make options similar to setup*/);
		static bool destroy();


		static bool refresh();
		static bool resize(const unsigned int & width, const unsigned int & height, const unsigned int & depth = 10);

		static unsigned int numObjects();

		static bool isSetup();

		static unsigned int height();
		static unsigned int width();
		static unsigned int depth();

	protected:
	private:
		std::map<unsigned int,renderObj*> m_objects; //!< Member variable "m_objects"
		unsigned int m_height;
		unsigned int m_width;
		unsigned int m_depth;
		bool m_isSetup;
};

#endif // RENDERER_H
