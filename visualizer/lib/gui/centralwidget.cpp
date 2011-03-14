#include "centralwidget.h"

CentralWidget::CentralWidget( QWidget *parent )
{
  m_renderWidget = new RenderWidget( this );
  m_widgetLayout = new QVBoxLayout( this );

  
  setLayout( m_widgetLayout );

}
