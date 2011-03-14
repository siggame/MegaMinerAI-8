#include "gui.h"

bool GUI::reg( const unsigned int& id, guiObj *obj )
{
  if( !isInit() )
    return false;

  if( get()->m_objects.find( id ) != get()->m_objects.end() )
    return false;

  get()->m_objects[id] = obj;
  return true;
}

bool GUI::del( const unsigned int& id )
{
  if( !isInit() )
    return false;

  if( get()->m_objects.find(id) == get()->m_objects.end() )
    return false;

  get()->m_objects.erase( id );
  return true;
}

bool GUI::setup()
{
  if( !isInit() )
    return false;

  return get()->doSetup();
}

bool GUI::clear()
{
  if( !isInit() )
    return false;

  get()->m_objects.clear();
  return true;
}

guiObj* GUI::getGUIObject( const unsigned int id )
{
  if( !isInit() )
    return NULL;

  if( get()->m_objects.find(id) == get()->m_objects.end() )
    return NULL;

  return get()->m_objects[id];
}

bool GUI::create()
{
  if( !Singleton<GUI>::create() )
    return false;
  return setup();
}

bool GUI::destroy()
{
  if( !isInit() )
    return false;
  if( !clear() )
    return false;

  return Singleton<GUI>::destroy();
}

unsigned int GUI::numObjects()
{
  if( !isInit() )
    return 0;

  return get()->m_objects.size();
}

bool GUI::isSetup()
{
  if( !isInit() )
    return false;

  return get()->m_isSetup;
}
#include <iostream>
using namespace std;

void GUI::resizeEvent( QResizeEvent* evt )
{
  QMainWindow::resizeEvent( evt );

}

bool GUI::doSetup()
{

  m_centralWidget = new CentralWidget( this );
  setCentralWidget( m_centralWidget );

  setWindowState( 
      windowState() 
      | Qt::WindowActive 
      | Qt::WindowMaximized 
      );

  show();
  return true;
}
