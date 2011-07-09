#ifndef RENDERWIDGET_H
#define RENDERWIDGET_H

#include <QtOpenGL>
#include "../selectionrender/selectionrender.h"

class RenderWidget: public QGLWidget
{
  public:
    RenderWidget( QWidget *parent );
    ~RenderWidget();
    void initializeGL();

    void resizeEvent( QResizeEvent *evt );
  
  private:
    //Old unit selection code we're bringing forward
    void mousePressEvent( QMouseEvent *event );
    void mouseReleaseEvent( QMouseEvent *event );
    void mouseMoveEvent( QMouseEvent *event );

    bool leftButtonDown;
    bool leftButtonDrag;

    int currentX;
    int currentY;

    int initialX;
    int initialY;

    static const int m_DRAG_DISTANCE = 6;

};

#endif
