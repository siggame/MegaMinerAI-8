INCLUDEPATH += ./interfaces/ \
    ./lib
PPATHS += ./lib/gameobject/ \
    ./lib/manager/ \
    ./lib/mutex/ \
    ./lib/threadler/ \
    ./lib/optionsmanager/ \
    ./lib/renderer/ \
    ./lib/resourcemanager/ \
    ./lib/timemanager/ \
    ./lib/gameobject/ \
    ./lib/gui/ 
SOURCES += main.cpp \
    ./lib/gameobject/*.cpp \
    ./lib/mutex/*.cpp \
    ./lib/threadler/*.cpp \
    ./lib/optionsmanager/*.cpp \
    ./lib/gui/*.cpp \
    ./lib/games/*.cpp \
    ./lib/timemanager/*.cpp \
    ./lib/*.cpp \
    ./lib/resourcemanager/*.cpp \
    ./lib/objectmanager/*.cpp \
    ./lib/selectionrender/*.cpp \
    ./lib/renderer/*.cpp \
    ./lib/renderer/textRenderer/*.cpp
MOC = moc
HEADERS += ./lib/manager/*.h \
    ./lib/timemanager/*.h \
    ./lib/gameobject/*.h \
    ./lib/mutex/*.h \
    ./lib/threadler/*.h \
    ./lib/optionsmanager/*.h \
    ./lib/renderer/*.h* \
    ./lib/gui/*.h \
    ./lib/objectmanager/*.h \
    ./lib/goc_controlbar.h \
    ./lib/*.h \
    ./lib/selectionrender/*.h \
    ./lib/resourcemanager/*.h \
    ./lib/renderer/textRenderer/*.h \
    ./interfaces/*.h
QMAKE_CFLAGS_DEBUG += -pg
QMAKE_CXXFLAGS_DEBUG += -pg
QMAKE_LFLAGS_DEBUG += -pg
CONFIG += debug
QT += opengl
SUBDIRS += tools 
OTHER_FILES += 
debug:DEFINES += __DEBUG__
