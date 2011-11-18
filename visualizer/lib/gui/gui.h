///////////////////////////////////////////////////////////////////////////////
/// @file gui.h
/// @description Contains the GUI interface used by the core visualizer
///////////////////////////////////////////////////////////////////////////////
#ifndef GUI_H
#define GUI_H

#include "decompress/bzlib.h"
#include "centralwidget.h"
#include "controlbar.h"
#include "../timemanager/timeManager.h"

#include <QtGui>
#include <QMainWindow>
#include <QTextEdit>
#include <QStringList>
#include <map>
#include <QHttp>

#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>

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
/// @fn _GUI::_clear();
/// @brief Clears all the objects registered
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn _GUI::dropEvent( QDropEvent* evt )
/// @brief This function is triggered automatically by Qt when an object, 
/// typically a file, is dropped onto the visualizer.  If the object dropped 
/// on the visualizer is a gamelog, then the visualizer will open it.
/// @param evt The details of the drop event.  This object is typically 
/// managed by Qt.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn _GUI::dragEnterEvent( QDragEnterEvent *evt )
/// @brief This function is triggered automatically by Qt when an object 
/// is dragged over the visualizer.  
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn _GUI::update()
/// @brief When triggered tell the control bar to update
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn _GUI::closeGUI()
/// @brief When triggered, the visualizer closes.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn _GUI::getControlBar()
/// @brief This returns the current control bar being used if we decide to go
/// for a modular approach to this.
/// @note May be removed in future versions of the visualizer.
/// @return guiObj* A pointer to a control bar guiObj
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn _GUI::appendConsole( string line ) 
/// @brief This function appends text to the console, like talks and debugging
/// commands.
/// @param line The line to be outputted to the console.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn _GUI::appendConsole( QString line ) 
/// @brief This function appends text to the console, like talks and debugging
/// commands.
/// @param line The line to be outputted to the console.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn _GUI::clearConsole()
/// @brief This function clears the console completely.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn _GUI::getFullScreen()
/// @brief Returns whether or not the visualizer is in fullscreen mode or not.
/// @return bool Representing the fullscreeniness of the visualizer.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn _GUI::setFullscreen( bool full )
/// @brief Sets puts the visualizer in fullscreen mode or releases it from
/// it.
/// @param full If true is passed, the visualizer is put into fullscreen mode.
/// If false is passed, the visualizer is released from fullscreen mode.
///////////////////////////////////////////////////////////////////////////////

/// @TODO Turn this into a module
class _GUI : public QMainWindow, public IGUI
{
  Q_OBJECT
  Q_INTERFACES( visualizer::IGUI );

  friend class RenderWidget;

  public:
    _GUI() : m_isSetup(false) {};
    ~_GUI();

    /// @TODO Revise
    static bool setup();
    /// @NOTE Why does this return a boolean?  
    bool clear();

    /// @TODO Revise
    bool create();
    bool destroy();

    /// @TODO Remove
    bool isSetup();

    /// EVENTS
    void dragEnterEvent( QDragEnterEvent *evt );
    void dropEvent( QDropEvent* evt );
    void resizeEvent( QResizeEvent* evt );

    void requestGamelog();
    bool loadInProgress() const;

    /// GAME SPECIFIC.  NEED TO BE MOVED ELSEWHERE
    void loadGamelog( std::string gamelog );
    void loadGamestring( char *log, const size_t& length );

    void update();
    void closeGUI();

    /// @TODO Revise or remove until we decide we want to switch out control bars
    ControlBar * getControlBar();

    void appendConsole( string line );
    void appendConsole( QString line );
    void clearConsole();

    bool getFullScreen();
    void setFullScreen(bool);

  private slots:

    void displayError( const QAbstractSocket::SocketError& err );
    void loadThatShit( bool err );

    void closeEvent( QCloseEvent* event );
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

    void newConnect();
    void newReadyConnect();

  public:

    /// @TODO This will probably have to change.
    QTableWidget* getGlobalStats();
    QTableWidget* getSelectionStats();
    QTableWidget* getIndividualStats();

  private:
    QHttp* m_http;

    bool m_loadInProgress;

#if 0
    QTcpServer* m_server;
    QTcpServer* m_visReadyServer;
#endif
    QTcpSocket* m_sock;

    QTableWidget * m_globalStats;
    QTableWidget * m_selectionStats;
    QTableWidget * m_individualStats;

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
