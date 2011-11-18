#ifndef SELECTIONRENDER_H
#define SELECTIONRENDER_H
#include "common.h"

namespace visualizer
{

/* The SelectionRender object assists with drawing the selection box that
 * appears when clicking and dragging to highlight interesting units.
 */

class _SelectionRender 
{
  public:
    _SelectionRender()
    {
      m_updated = false;              //Finished dragging
      m_dragging = false;             //Currently dragging

      m_X1 = m_Y1 = m_X2 = m_Y2 = 0;
    }
                                 //X1, Y1, X2, Y2 Screen Resolution
    void setSelectionBox(int, int, int, int);
    int getX1() { return m_X1; }
    int getX2() { return m_X2; }
    int getY1() { return m_Y1; }
    int getY2() { return m_Y2; }

    bool getUpdated();
    void setUpdated(bool);

    bool getDragging();
    void setDragging(bool);
    void update() {};

    static void setup();
    static void destroy();

  private:
    void renderAt(const unsigned int & turn, const unsigned int & frame);

    bool m_updated;              //Finished dragging
    bool m_dragging;             //Currently dragging

    int m_X1, m_Y1, m_X2, m_Y2;
};

extern _SelectionRender *SelectionRender;

} // visualizer

#endif
