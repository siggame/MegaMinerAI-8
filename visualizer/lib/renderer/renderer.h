#ifndef RENDERER_H
#define RENDERER_H

#include <map>
#include <list>
#include <set>
#include <QTableWidget>
#include <QtOpenGL>
#include <string>
#include "textRenderer/drawGLFont.h"
#include "../optionsmanager/optionsman.h"
#include "../objectmanager/objectmanager.h"
#include "../gui/renderwidget.h"
#include "../animationengine/animationengine.h"
#include "../resourcemanager/resourceman.h"

#include "../timemanager/timeManager.h"

#include "../../interfaces/irenderer.h"
#include "common.h"

namespace visualizer
{

#define renderHeightName  "renderHeight"
#define renderWidthName   "renderWidth"
#define renderDepthName   "renderDepth"
#define renderDirsName    "renderDirections"

  class RenderWidget;
  class _Renderer : public UpdateNeeded, public Module, public IRenderer
  {
    Q_INTERFACES( IRenderer );
    public:

      _Renderer()
      {
	  	  m_isSetup = false;
        m_height = m_width = m_depth = 0;
      }

      bool registerConstantObj( const unsigned int& id, renderObj* obj );
      bool deleteConstantObj( const unsigned int& id );

      static void setup();
      static void destroy();
      void _setup();

      bool clear();

      bool create();

      void setParent( RenderWidget *parent );

      bool refresh();
      bool resize
        (
        const unsigned int & width,
        const unsigned int & height,
        const unsigned int & depth = 1
        );

      bool isSetup();

      unsigned int height();
      unsigned int width();
      unsigned int depth();

      bool update
        (
        const unsigned int & turn,
        const unsigned int & frame
        );

      void update();

      void setColor
        (
        const Color& c
        ) const;

      void drawQuad
        (
        const float& x,
        const float& y,
        const float& w,
        const float& h,
        const float& z = 0.0f
        ) const;

      void drawTexturedQuad
        (
        const float& x,
        const float& y,
        const float& w, 
        const float& h, 
        const std::string& resource,
        const float& z = 0.0f
        ) const;

      void drawAnimQuad
        (
        const float& x,
        const float& y,
        const float& w, 
        const float& h, 
        const std::string& resource, 
        const int& frameNumber = 0,
        const float& z = 0.0f
        ) const;

      void drawProgressBar
        (
        const float& x,
        const float& y, 
        const float& w, 
        const float& h,
        const float& percent,
        const Color& color = Color( 0, 0, 0, 1 ),
        const float& lineWidth = 1,
        const float& z = 0.0f
        ) const; 

      void drawText
        (
        const float& x,
        const float& y,
        const std::string& line, 
        const float& size = 15.0f, 
        const Alignment& a = Left
        ) const;

    protected:
    private:
      unsigned int m_height;
      unsigned int m_width;
      unsigned int m_depth;
      bool m_isSetup;

      std::map<int, renderObj*> m_renderConstant;
      RenderWidget *m_parent;

  };

  extern _Renderer *Renderer;

} // visualizer

#endif                           // RENDERER_H
