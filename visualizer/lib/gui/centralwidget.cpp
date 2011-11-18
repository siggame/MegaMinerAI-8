#include "centralwidget.h"
#include "gui.h"
#include <QLabel>

namespace visualizer
{

  CentralWidget::~CentralWidget()
  {
    delete m_renderWidget;
    delete m_widgetLayout;

  }


  CentralWidget::CentralWidget( QWidget* /*parent*/ )
  {
    m_renderWidget = new RenderWidget( this );
    m_widgetLayout = new QVBoxLayout( this );

    m_widgetLayout->setContentsMargins( 0, 0, 0, 0 );
    m_widgetLayout->addWidget( m_renderWidget );

    setLayout( m_widgetLayout );
  }

} // visualizer
