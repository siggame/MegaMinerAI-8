INCLUDEPATH += ./lib/parser \
    ./lib/parser/sexp \
    ./interfaces/ \
    ./lib
win32:LIBS += ./lib/parser/sexp/sexpXP.a
else:LIBS += ./lib/parser/sexp/sexp.a
PPATHS += ./lib/gameobject/ \
    ./lib/manager/ \
    ./lib/mutex/ \
    ./lib/threadler/ \
    ./lib/optionsmanager/ \
    ./lib/renderer/ \
    ./lib/resourcemanager/ \
    ./lib/timemanager/ \
    ./lib/gameobject/ \
    ./lib/gui/ \
    ./lib/parser/
SOURCES += main.cpp \
    ./lib/gameobject/*.cpp \
    ./lib/mutex/*.cpp \
    ./lib/threadler/*.cpp \
    ./lib/optionsmanager/*.cpp \
    ./lib/gui/*.cpp \
    ./lib/timemanager/*.cpp \
    ./lib/parser/parser.cpp \
    ./lib/parser/structures.cpp \
    ./lib/*.cpp \
    ./lib/resourcemanager/*.cpp \
    ./piracy/*.cpp \
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
    ./lib/parser/*.h \
    ./lib/gui/*.h \
    ./lib/objectmanager/*.h \
    ./lib/goc_controlbar.h \
    ./lib/*.h \
    ./lib/selectionrender/*.h \
    ./piracy/*.h \
    ./lib/resourcemanager/*.h \
    ./lib/renderer/textRenderer/*.h \
    ./interfaces/*.h
QMAKE_CFLAGS_DEBUG += -pg
QMAKE_CXXFLAGS_DEBUG += -pg
QMAKE_LFLAGS_DEBUG += -pg
CONFIG += debug
QT += opengl
SUBDIRS += parser \
    tools
OTHER_FILES += 
debug:DEFINES += __DEBUG__
