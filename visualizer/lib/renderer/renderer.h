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

#include "../timemanager/timeManager.h"
#include "animatable.h"

#include "../../interfaces/irenderer.h"
#include "common.h"

namespace visualizer
{

#define renderHeightName "renderHeight"
#define renderWidthName "renderWidth"
#define renderDepthName "renderDepth"
#define renderDirsName  "renderDirections"

class RenderWidget;

struct Talks
{
  int id;
  string message;
};

struct Stats
{
  Stats()
  {
    gold = 0;
    pirates = 0;
    avgPirateHealth = 0;
    avgPirateGold = 0;
    ports = 0;
    ships = 0;
    avgShipHealth = 0;
    avgShipGold = 0;
    treasures = 0;
    portGold = 0;
  }

  Stats& operator += ( const Stats& rhs )
  {
    gold += rhs.gold;
    pirates += rhs.pirates;
    avgPirateHealth += rhs.avgPirateHealth;
    avgPirateGold += rhs.avgPirateGold;
    ships += rhs.ships;
    avgShipHealth += rhs.avgShipHealth;
    avgShipGold += rhs.avgShipGold;
    treasures += rhs.treasures;
    ports += rhs.ports;
    return *this;
  }

  int portGold;
  int ports;
  int gold;
  int pirates;
  int avgPirateHealth;
  int avgPirateGold;
  int ships;
  int avgShipHealth;
  int avgShipGold;
  int treasures;

  void final()
  {
    if( pirates )
    {
      avgPirateGold /= pirates;
      avgPirateHealth /= pirates;
    }

    if( ships )
    {
      avgShipGold /= ships;
      avgShipHealth /= ships;
    }
  }

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

    void registerFrameContainer( std::vector<std::list<SmartPointer<Animatable> > >* frameList );

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
