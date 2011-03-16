#ifndef RENDERWIDGET_H
#define RENDERWIDGET_H

#include <QtOpenGL>
#include "../renderer/renderer.h"


class RenderWidget: public QGLWidget
{
public:
  RenderWidget( QWidget *parent );
  ~RenderWidget();
  void initializeGL();

  void resizeEvent( QResizeEvent *evt );

};

#endif
