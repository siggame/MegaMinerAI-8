#ifndef RENDERER_H
#define RENDERER_H

#include <map>
#include <list>
#include <set>
#include <QTableWidget>
#include <GL/gl.h>
#include <string>
#include "textRenderer/drawGLFont.h"
#include "../optionsmanager/optionsman.h"
#include "../objectmanager/objectmanager.h"
#include "../gocfamily_render.h"
#include "../gocfamily_location.h"
#include "../gui/gui.h"
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

  struct Talks
  {
    int id;
    string message;
  };

  class _Renderer : public UpdateNeeded, public Module, public IRenderer
  {
    Q_INTERFACES( IRenderer );
    public:

      _Renderer()
      {
        //m_frames = 0;
      }

      bool registerConstantObj( const unsigned int& id, renderObj* obj );
      bool deleteConstantObj( const unsigned int& id );

      static void setup();
      static void destroy();
      void _setup();

      bool clear();

      //renderObj * getRenderObject(const unsigned int id);

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
        const float& r,
        const float& g, 
        const float& b,
        const float& a = 1.0f
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
        );

      void drawProgressBar
        (
        const float& x,
        const float& y, 
        const float& w, 
        const float& h,
        const float& percent,
        const float& z = 0.0f
        );

      //void registerFrameContainer( AnimSequence* frameList );

    protected:
    private:
      unsigned int m_height;
      unsigned int m_width;
      unsigned int m_depth;
      bool m_isSetup;

      //FrameContainer m_frames;

      std::map<int, renderObj*> m_renderConstant;
      RenderWidget *m_parent;

  };

  extern _Renderer *Renderer;

} // visualizer

#endif                           // RENDERER_H
