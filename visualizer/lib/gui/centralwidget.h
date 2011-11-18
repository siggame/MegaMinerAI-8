//////////////////////////////////////////////////////////////////////////////
/// @file centralwidget.h
/// @brief The class declaration for the central widget which contains the 
/// rendering window.
//////////////////////////////////////////////////////////////////////////////
#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>
#include "renderwidget.h"
#include "controlbar.h"
#include "../../interfaces/icentralwidget.h"

namespace visualizer
{

  class CentralWidget: public QWidget, public ICentralWidget
  {
    Q_INTERFACES( ICentralWidget );
    public:
      CentralWidget( QWidget *parent = 0 );
      ~CentralWidget();

    private:
      // Important Widgets
      ControlBar *m_controlBarWidget;
      RenderWidget *m_renderWidget;

      // Layout Widgets
      QVBoxLayout *m_widgetLayout;

  };

} // visualizer

#endif
