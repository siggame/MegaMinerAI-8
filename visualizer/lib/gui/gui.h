#ifndef GUI_H
#define GUI_H

#include "centralwidget.h"
#include "../singleton.h"
#include "../gocfamily_gui.h"
#include <QtGui>
#include <QMainWindow>
#include <map>
#include <string>

typedef GOCFamily_GUI guiObj;

class GUI : public QMainWindow, public Singleton<GUI>
{
  Q_OBJECT
public:
  GUI();
  static bool reg( const std::string& id, guiObj *obj );
  static bool del( const std::string& id );

  static bool setup();
  static bool clear();

  static guiObj *getGUIObject( const std::string& id );

  static bool create();
  static bool destroy();

  static unsigned int numObjects();

  static bool isSetup();

  void resizeEvent( QResizeEvent* evt );

private slots:
  void helpContents();

private:
  std::map<std::string, guiObj*> m_objects;
  bool m_isSetup;

  CentralWidget *m_centralWidget;

  bool doSetup();
  void createActions();
  void createMenus();

  // Actions
  QAction *m_helpContents;
};

#endif
