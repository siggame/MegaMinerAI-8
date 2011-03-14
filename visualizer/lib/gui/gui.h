#ifndef GUI_H
#define GUI_H

#include "../singleton.h"
#include "../gocfamily_gui.h"
#include "centralwidget.h"
#include <QtGui>
#include <QMainWindow>
#include <map>

typedef GOCFamily_GUI guiObj;

class GUI : public QMainWindow, public Singleton<GUI>
{
public:
  static bool reg( const unsigned int& id, guiObj *obj );
  static bool del( const unsigned int& id );

  static bool setup();
  static bool clear();

  static guiObj *getGUIObject( const unsigned int id );

  static bool create();
  static bool destroy();

  static unsigned int numObjects();

  static bool isSetup();

  void resizeEvent( QResizeEvent* evt );

private slots:

private:
  std::map<unsigned int, guiObj*> m_objects;
  bool m_isSetup;

  CentralWidget *m_centralWidget;


  bool doSetup();
};

#endif
