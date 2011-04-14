#include "renderwidget.h"
#include "../../piracy/dupObj.h"

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

  Renderer<DupObj>::create();
  Renderer<DupObj>::setParent( this );

}

void RenderWidget::resizeEvent( QResizeEvent *evt )
{
  Renderer<DupObj>::resize( evt->size().width(), evt->size().height() );
}
