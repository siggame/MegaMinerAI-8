#ifndef RENDERER_H
#define RENDERER_H

#include "../singleton.h"
#include <map>
#include <GL/gl.h>
#include "textRenderer/drawGLFont.h"
#include "../optionsmanager/optionsman.h"
#include "../gocfamily_render.h"
#include "../gui/renderwidget.h"
#include "duplicatelist/dupObj.h"
#include "lookupTable/lookuptable.h"

//this is a place holder
typedef GameObject renderObj;

#define renderHeightName "renderHeight"
#define renderWidthName "renderWidth"
#define renderDepthName "renderDepth"
#define renderDirsName 	"renderDirections"

class RenderWidget;

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

    static void setParent( RenderWidget *parent );

		static bool refresh();
		static bool resize(const unsigned int & width, const unsigned int & height, const unsigned int & depth = 1);

		static unsigned int numObjects();

		static bool isSetup();

		static unsigned int height();
		static unsigned int width();
		static unsigned int depth();


		static LookupTable<renderObj> & lookupTable();

	protected:
	private:
		std::map<unsigned int,renderObj*> m_objects; //!< Member variable "m_objects"
		LookupTable<renderObj> m_lookupTable;
		unsigned int m_height;
		unsigned int m_width;
		unsigned int m_depth;
		bool m_isSetup;

		DupObj **** m_duplicateList;
		unsigned int m_dupListDirs;
		std::vector<DupObj> m_renderList;

		static void updateLocation(const unsigned int & x, const unsigned int & y, const unsigned int & z, const unsigned int & dir,
							const unsigned int & time, DupObj obj);

    RenderWidget *m_parent;
};

#endif // RENDERER_H
