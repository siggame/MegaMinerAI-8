#include "renderwidget.h"

#include <iostream>
using namespace std;

RenderWidget::RenderWidget( QWidget *parent )
: QGLWidget( QGLFormat( QGL::SampleBuffers ), parent )
{

}

RenderWidget::~RenderWidget()
{
}

void RenderWidget::initializeGL()
{

  Renderer::create();

}

void RenderWidget::resizeEvent( QResizeEvent *evt )
{
  Renderer::resize( evt->size().width(), evt->size().height() );
}
