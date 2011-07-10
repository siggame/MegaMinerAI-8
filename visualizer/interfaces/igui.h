#ifndef IGUI_H
#define IGUI_H

#include <QTableWidget>
#include <QString>
#include <string>
#include "../lib/gocfamily_gui.h"
typedef GOCFamily_GUI guiObj;

class IGUI
{ 
  public:
    virtual bool reg( const std::string& id, guiObj *obj ) = 0;
    virtual bool del( const std::string& id ) = 0;

    virtual guiObj* getGUIObject( const std::string& id ) = 0;

    virtual unsigned int numObjects() = 0;

    virtual bool isSetup() = 0;

    virtual void update() = 0;
    virtual void closeGUI() = 0;

    virtual void appendConsole( std::string line ) = 0;
    virtual void appendConsole( QString line ) = 0;
    virtual void clearConsole() = 0;

    virtual bool getFullScreen() = 0;
    virtual void setFullScreen( bool ) = 0;

    virtual QTableWidget* getGlobalStats() = 0;
    virtual QTableWidget* getSelectionStats() = 0;
    virtual QTableWidget* getIndividualStats() = 0;

};

#endif
