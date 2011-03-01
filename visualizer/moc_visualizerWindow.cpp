/****************************************************************************
** Meta object code from reading C++ file 'visualizerWindow.h'
**
** Created: Mon Feb 21 16:32:01 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "visualizerWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'visualizerWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_UnitSelection[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_UnitSelection[] = {
    "UnitSelection\0"
};

const QMetaObject UnitSelection::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_UnitSelection,
      qt_meta_data_UnitSelection, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &UnitSelection::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *UnitSelection::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *UnitSelection::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UnitSelection))
        return static_cast<void*>(const_cast< UnitSelection*>(this));
    return QLabel::qt_metacast(_clname);
}

int UnitSelection::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_Scoreboard[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_Scoreboard[] = {
    "Scoreboard\0"
};

const QMetaObject Scoreboard::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Scoreboard,
      qt_meta_data_Scoreboard, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Scoreboard::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Scoreboard::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Scoreboard::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Scoreboard))
        return static_cast<void*>(const_cast< Scoreboard*>(this));
    return QWidget::qt_metacast(_clname);
}

int Scoreboard::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_VisualizerWindow[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x08,
      32,   17,   17,   17, 0x08,
      47,   17,   17,   17, 0x08,
      61,   17,   17,   17, 0x08,
      80,   17,   17,   17, 0x08,
      98,   17,   17,   17, 0x08,
     114,   17,   17,   17, 0x08,
     131,   17,   17,   17, 0x08,
     149,   17,   17,   17, 0x08,
     164,   17,   17,   17, 0x08,
     180,   17,   17,   17, 0x08,
     192,   17,   17,   17, 0x08,
     207,   17,   17,   17, 0x08,
     227,   17,   17,   17, 0x08,
     257,  251,   17,   17, 0x08,
     283,   17,   17,   17, 0x08,
     297,   17,   17,   17, 0x08,
     311,   17,   17,   17, 0x08,
     332,   17,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_VisualizerWindow[] = {
    "VisualizerWindow\0\0openGamelog()\0"
    "closeGamelog()\0exitProgram()\0"
    "toggleFullScreen()\0closeFullScreen()\0"
    "toggleMapGrid()\0loadBackground()\0"
    "clearBackground()\0advanceFrame()\0"
    "previousFrame()\0playPause()\0viewGameDocs()\0"
    "controlSliderDrag()\0controlSliderReleased()\0"
    "frame\0controlSliderChanged(int)\0"
    "stopClicked()\0playClicked()\0"
    "fastForwardClicked()\0rewindClicked()\0"
};

const QMetaObject VisualizerWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_VisualizerWindow,
      qt_meta_data_VisualizerWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &VisualizerWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *VisualizerWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *VisualizerWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VisualizerWindow))
        return static_cast<void*>(const_cast< VisualizerWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int VisualizerWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: openGamelog(); break;
        case 1: closeGamelog(); break;
        case 2: exitProgram(); break;
        case 3: toggleFullScreen(); break;
        case 4: closeFullScreen(); break;
        case 5: toggleMapGrid(); break;
        case 6: loadBackground(); break;
        case 7: clearBackground(); break;
        case 8: advanceFrame(); break;
        case 9: previousFrame(); break;
        case 10: playPause(); break;
        case 11: viewGameDocs(); break;
        case 12: controlSliderDrag(); break;
        case 13: controlSliderReleased(); break;
        case 14: controlSliderChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: stopClicked(); break;
        case 16: playClicked(); break;
        case 17: fastForwardClicked(); break;
        case 18: rewindClicked(); break;
        default: ;
        }
        _id -= 19;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
