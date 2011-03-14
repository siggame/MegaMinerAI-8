#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>
#include "renderwidget.h"
#include "../goc_controlbar.h"

class CentralWidget: public QWidget
{
public:
  CentralWidget( QWidget *parent = 0 );

private:
  GOC_ControlBar *m_controlBarWidget;
  RenderWidget *m_renderWidget;
  QVBoxLayout *m_widgetLayout;

};


#endif
