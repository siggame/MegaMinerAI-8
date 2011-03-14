#include "renderwidget.h"

RenderWidget::RenderWidget( QWidget *parent )
  QGLWidget( QGLFormat( QGL::SampleBuffers ), parent )
{

}

void RenderWidget::initializeGL()
{

  Renderer::create();

}
