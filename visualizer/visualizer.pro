INCLUDEPATH += ./lib/parser \
    ./lib/parser/sexp
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
    ./lib/gocfamily_data.cpp
MOC = moc
HEADERS += *.h \
    ./lib/manager/*.h \
    ./lib/timemanager/*.h \
    ./lib/gameobject/*.h \
    ./lib/mutex/*.h \
    ./lib/threadler/*.h \
    ./lib/optionsmanager/*.h \
    ./lib/renderer/*.h* \
    ./lib/parser/*.h \
    ./lib/gui/*.h \
    ./piracy/*.h \
    ./lib/objectmanager/*.h \
    ./lib/timeline/timeline.h \
    ./lib/timeline/timeline.hpp \
    ./lib/timeline/lookupTable/lookuptable.h \
    ./lib/timeline/lookupTable/lookuptable.hpp \
    ./lib/goc_controlbar.h \
    ./lib/gocfamily_controlbar.h \
    ./lib/gocfamily_data.h \
    ./lib/gocfamily_gui.h \
    ./lib/gocfamily_guitoolset.h \
    ./lib/gocfamily_render.h \
    ./lib/singleton.h
CONFIG += debug
QT += opengl
SUBDIRS += parser \
    tools
