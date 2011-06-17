#ifndef RENDERER_H
#define RENDERER_H

// TODO: Add more includes.  Not nearly enough
#include "../singleton.h"
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

//this is a place holder
typedef GameObject renderObj;

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

template <typename DupObject>
class Renderer : public Singleton< Renderer< DupObject > >
{
  //BOOST_CONCEPT_ASSERT((UnsignedInteger<DupObject::index>));

  public:
    //static bool reg(const unsigned int & id, renderObj * obj);
    //static bool del(const unsigned int & id);

    static bool registerConstantObj( const unsigned int& id, renderObj* obj );
    static bool deleteConstantObj( const unsigned int& id );

    static bool setup(/**@todo make options*/);
    static bool clear();

    //static renderObj * getRenderObject(const unsigned int id);

    static bool create();
    static bool destroy();

    static void setParent( RenderWidget *parent );

    static bool refresh();
    static bool resize(const unsigned int & width, const unsigned int & height, 
      const unsigned int & depth = 1);

    //static unsigned int numObjects();

    static bool isSetup();

    static unsigned int height();
    static unsigned int width();
    static unsigned int depth();

    static bool update(const unsigned int & turn, const unsigned int & frame);

  protected:
  private:
    //std::map<unsigned int,renderObj*> m_objects; //!< Member variable "m_objects"
    //LookupTable<renderObj> m_lookupTable;
    unsigned int m_height;
    unsigned int m_width;
    unsigned int m_depth;
    bool m_isSetup;

    DupObject **** m_duplicateList;
    unsigned int m_dupListDirs;
    std::vector<DupObject*> m_renderList;

    std::map<int, renderObj*> m_renderConstant;

    void individualStatColumnPopulate(int id, DupObject unit, int column );
    void selectionStatColumnPopulate( Stats multi, int column );
    void globalStatColumnPopulate( Stats multi, int column );
    void printGlobalStats( int c, int r, QString str );
    void printSelectedStats( int c, int r, QString str );
    void printIndividuals( int c, int r, QString str );
    void setNumIndividuals( int num );
    void printToTable( QTableWidget *w, int c, int r, QString str );
    void appendToConsole( string str );

    static void updateLocation(const unsigned int & x, const unsigned int & y, 
      const unsigned int & z, const unsigned int & dir, 
      const unsigned int & time, DupObject obj);

    typedef Singleton<Renderer<DupObject> > Single;
    typedef Renderer<DupObject> Render;

    RenderWidget *m_parent;

    set<int> selectedUnitIds;

    //static void multipleUnitStatColumnPopulate (Stats multi, int column);
};

#include "renderer.hpp"
#endif                           // RENDERER_H
