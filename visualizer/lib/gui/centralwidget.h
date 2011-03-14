#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>
#include "renderwidget.h"

class CentralWidget: public QWidget
{
  Q_OBJECT
public:
  CentralWidget( QWidget *parent = 0 );

private:
  RenderWidget *m_renderWidget;
  QVBoxLayout *m_widgetLayout;

};


#endif
