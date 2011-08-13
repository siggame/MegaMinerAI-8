///////////////////////////////////////////////////////////////////////////////
/// @file gui.h
/// @description Contains the GUI interface used by the core visualizer
///////////////////////////////////////////////////////////////////////////////
#ifndef GUI_H
#define GUI_H

#include "centralwidget.h"
#include "controlbar.h"
#include "../timemanager/timeManager.h"

#include <QtGui>
#include <QMainWindow>
#include <QTextEdit>
#include <QStringList>
#include <map>

#include "igui.h"

using namespace std;

namespace visualizer
{

///////////////////////////////////////////////////////////////////////////////
/// @class _GUI
/// @brief GUI object for drawing debugging info along with the QOpenGL 
//// Widget
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @function _GUI::_clear();
/// @brief Clears all the objects registered
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @function _GUI::dropEvent( QDropEvent* evt )
/// @brief This function is triggered automatically by Qt when an object, 
/// typically a file, is dropped onto the visualizer.  If the object dropped 
/// on the visualizer is a gamelog, then the visualizer will open it.
/// @param evt The details of the drop event.  This object is typically 
/// managed by Qt.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @function _GUI::dragEnterEvent( QDragEnterEvent *evt )
/// @brief This function is triggered automatically by Qt when an object 
/// is dragged over the visualizer.  
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @function _GUI::update()
/// @brief
///////////////////////////////////////////////////////////////////////////////

/// @TODO: Turn this into a module
class _GUI : public QMainWindow, public IGUI
{
  Q_OBJECT
  Q_INTERFACES( visualizer::IGUI );

  friend class RenderWidget;

  public:
    _GUI() : m_isSetup(false) {};
    ~_GUI();
    /// @TODO:  Remove these or revise these
    bool reg( const std::string& id, guiObj *obj );
    bool del( const std::string& id );

    /// @TODO: Revise
    static bool setup();
    /// @NOTE: Why does this return a boolean?  
    bool clear();

    /// @TODO: Remove or revise
    guiObj *getGUIObject( const std::string& id );

    /// @TODO: Revise
    bool create();
    bool destroy();
    unsigned int numObjects();

    /// @TODO: Remove
    bool isSetup();

    /// EVENTS
    void dragEnterEvent( QDragEnterEvent *evt );
    void dropEvent( QDropEvent* evt );
    void resizeEvent( QResizeEvent* evt );

    /// GAME SPECIFIC.  NEED TO BE MOVED ELSEWHERE
    void loadGamelog( std::string gamelog );

    void update();
    void closeGUI();

    ControlBar * getControlBar();

    void appendConsole( string line );
    void appendConsole( QString line );
    void clearConsole();

    bool getFullScreen();
    void setFullScreen(bool);

  private slots:
    void helpContents();
    void fileOpen();
    void toggleFullScreen();
    void togglePlayPause();
    void fastForwardShortcut();
    void rewindShortcut();
    void stepTurnForwardShortcut();
    void stepTurnBackShortcut();

    void catchEscapeKey();

    void turnPercentageShortcut1();
    void turnPercentageShortcut2();
    void turnPercentageShortcut3();
    void turnPercentageShortcut4();
    void turnPercentageShortcut5();
    void turnPercentageShortcut6();
    void turnPercentageShortcut7();
    void turnPercentageShortcut8();
    void turnPercentageShortcut9();
    void turnPercentageShortcut0();

  public:

    QTableWidget* getGlobalStats();
    QTableWidget* getSelectionStats();
    QTableWidget* getIndividualStats();

  private:

    QTableWidget * m_globalStats;
    QTableWidget * m_selectionStats;
    QTableWidget * m_individualStats;

    /// Container for the objects in the GUI
    std::map<std::string, guiObj*> m_objects;
    /// Setup?
    bool m_isSetup;

    //In full screen mode or not?
    bool fullScreen;

    /// Main widget for this window
    CentralWidget *m_centralWidget;

    /// Dock Widget For Debugging Info
    QDockWidget *m_dockWidget;

    /// Frame used to hold layout for widgets in dock
    QFrame *m_dockLayoutFrame;

    /// Layout For the Dock Widget
    QVBoxLayout *m_dockLayout;

    /// Console Area
    QTextEdit *m_consoleArea;

    /// Unit Stats Area
    QTabWidget * m_unitStatsArea;
    QStringList m_globalStatsVerticalLabels;
    QStringList m_globalStatsHorizontalLabels;
    QStringList m_selectionStatsVerticalLabels;
    QStringList m_selectionStatsHorizontalLabels;
    QStringList m_individualStatsVerticalLabels;
    QStringList m_individualStatsHorizontalLabels;

    /// Status Bar
    QStatusBar *m_statusBar;

    /// Control Bar
    ControlBar *m_controlBar;

    /// Debugging Toolset Widget Within the Dock
    GOCFamily_GUIToolSet *m_toolSetWidget;

    bool doSetup();
    void buildControlBar();
    void createActions();
    void createMenus();
    void buildToolSet();
    void initUnitStats();

    void turnPercentageCalc(int);

    // Actions
    QAction *m_helpContents;     /// Help->Contents

    QAction *m_fileOpen;         /// File->Open
    QAction *m_fileExit;         /// File->Exit

    QAction *toggleFullScreenAct;/// View -> Toggle Full Screen

    QString m_previousDirectory;
    QRect m_normalWindowGeometry;

};

extern _GUI *GUI;

}
#endif
