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
    ./lib/gocfamily_data.cpp \
    ./lib/selectionrender/*.cpp \
    lib/resourcemanager/resourceload.cpp \
    lib/resourcemanager/resourceman.cpp \
    lib/resourcemanager/textureload.cpp
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
    ./lib/singleton.h \
    ./lib/selectionrender/*.h \
    lib/gocfamily_location.h \
    piracy/piracylocations.h \
    lib/goc_owner.h \
    piracy/gold.h \
    piracy/objecttype.h \
    lib/resourcemanager/resource.h \
    lib/resourcemanager/resourceman.h \
    lib/resourcemanager/texture.h \
    lib/resourcemanager/typedefs.h
QMAKE_CFLAGS_DEBUG += -pg
QMAKE_CXXFLAGS_DEBUG += -pg
QMAKE_LFLAGS_DEBUG += -pg
CONFIG += debug
QT += opengl
SUBDIRS += parser \
    tools
OTHER_FILES += lib/resourcemanager/resourceman.o
