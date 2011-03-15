#ifndef GUI_H
#define GUI_H

#include "centralwidget.h"
#include "../singleton.h"
#include "../gocfamily_gui.h"
#include <QtGui>
#include <QMainWindow>
#include <QTextEdit>
#include <map>
#include <string>

typedef GOCFamily_GUI guiObj;


////////////////////////////////////////////////////////////////
/// @class    GUI
/// @brief    GUI object for drawing debugging info along with
///           the QOpenGL Widget
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
/// @fn       reg( const std::string& id, guiObj *obj )
/// @brief    Registers the desired object with the gui.  Must 
///           do for controlBar, debugWindow, etc.
/// @param    id Unique identifier for this object.
/// @param    obj The object we're registering
/// @pre      id must be unique and obj must be a valid object
/// @post     The object will be registered with the GUI
/// @return   bool True if successfully registered. False, 
///           if otherwise.  
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
/// @fn       del( const std::string& id )
/// @brief    Unregisters the desired object from the gui.
/// @param    id Unique identifier to delete an object.
/// @pre      id must refer to an object within GUI
/// @post     The object will be unregistered with the GUI
/// @return   bool True if successfully unregistered. 
///           False, if otherwise.  
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
/// @fn       setup()
/// @brief    Set's up the GUI along with the singleton   
/// @pre      Object must have been created before hand
/// @post     The GUI will be all setup
/// @return   bool True if successfully setup.  
///           False, if otherwise.  
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
/// @fn       clear()
/// @brief    Destroys the instance to the GUI.   
/// @pre      GUI must exist for it to be destroyed.
/// @post     The GUI instance will be destroyed.
/// @return   bool True if successfully destroyed.  
///           False, if otherwise  
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
/// @fn       getGUIObject( const std::string& id )
/// @brief    Get the desired object by name  
/// @param    id Unique identifier to get an object
/// @pre      Object must be registered with id
/// @post     The pointer to the object of id will be returned
/// @return   guiObj* The desired object if found, zero if otherwise.  
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
/// @fn       create()
/// @brief    Set's up the GUI along with the singleton   
/// @pre      Object must have been created before hand
/// @post     The GUI will be all setup
/// @return   bool True if successfully setup.  
///           False, if otherwise.  
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
/// @fn       destroy()
/// @brief    Destroys the instance to the GUI.   
/// @pre      GUI must exist for it to be destroyed.
/// @post     The GUI instance will be destroyed.
/// @return   bool True if successfully destroyed.  
///           False, if otherwise  
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
/// @fn       numObjects()
/// @brief    Get the number of registered objects in GUI   
/// @pre      None
/// @post     Number of registered objects will be returned.
/// @return   unsigned int representing the number of objects 
///           in the GUI  
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
/// @fn       isSetup()
/// @brief    Is the GUI object setup properly?   
/// @pre      None
/// @post     Returns whether GUI is setup or not
/// @return   bool True if setup.  False, if otherwise.  
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
/// @fn       resizeEvents( QResizeEvent* evt )
/// @brief    Deal with a resize action   
/// @param    evt Contains various data related to the event.
/// @pre      None
/// @post     Appropriately deals with the window getting resized.
/// @return   None  
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
/// @fn       helpContents()
/// @brief    Respond to Help->Contents   
/// @pre      None
/// @post     Opens up a URL to the help page.
/// @return   None  
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
/// @fn       doSetup()
/// @brief    Setup the window  
/// @pre      None
/// @post     Sets up the Window with the QOpenGL object, menus, etc.
/// @return   bool True if everything went alright.  
///           False, if otherwise. 
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
/// @fn       createActions()
/// @brief    Build the actions needed for this GUI   
/// @pre      None
/// @post     Action set will be built
/// @return   None  
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
/// @fn       createMenus()
/// @brief    Build the menus for this window   
/// @pre      None
/// @post     Menus will be built
/// @return   None  
////////////////////////////////////////////////////////////////

class GUI : public QMainWindow, public Singleton<GUI>
{
  Q_OBJECT
public:
  ~GUI();
  static bool reg( const std::string& id, guiObj *obj );
  static bool del( const std::string& id );

  static bool setup();
  static bool clear();

  static guiObj *getGUIObject( const std::string& id );

  static bool create();
  static bool destroy();

  static unsigned int numObjects();

  static bool isSetup();

  /// EVENTS
  void dragEnterEvent( QDragEnterEvent *evt );
  void dropEvent( QDropEvent* evt );
  void resizeEvent( QResizeEvent* evt );

private slots:
  void helpContents();

private:
  /// Container for the objects in the GUI
  std::map<std::string, guiObj*> m_objects;
  /// Setup?
  bool m_isSetup;

  /// Main widget for this window
  CentralWidget *m_centralWidget; 

  /// Dock Widget For Debugging Info
  QDockWidget *m_dockWidget;

  /// Frame used to hold layout for widgets in dock
  QFrame *m_dockLayoutFrame; 

  /// Layout For the Dock Widget
  QHBoxLayout *m_dockLayout;

  /// Console Area
  QTextEdit *m_consoleArea;

  /// Debugging Toolset Widget Within the Dock
  GOCFamily_GUIToolSet *m_toolSetWidget;

  bool doSetup();
  void createActions();
  void createMenus();
  void buildToolSet();

  // Actions
  QAction *m_helpContents; /// Help->Contents
};

#endif
