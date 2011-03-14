#ifndef RENDERWIDGET_H
#define RENDERWIDGET_H

#include <QtOpenGL>
#include "../renderer/renderer.h"


class RenderWidget: public QGLWidget
{
public:
  RenderWidget( QWidget *parent );
  void initializeGL();


};

#endif
