INCLUDEPATH += ../interfaces \
  ../parser \
  ../parser/sexp \
  ../common/
DEPENDPATH += ../common/
win32:LIBS += ./parser/sexp/sexpXP.a
else:LIBS += ./parser/sexp/sexp.a
MOC = moc
TEMPLATE = lib
TARGET = modular
SOURCES += *.cpp

HEADERS += modular.h

QMAKE_CFLAGS_DEBUG += -pg
QMAKE_CXXFLAGS_DEBUG += -pg
QMAKE_LFLAGS_DEBUG += -pg
CONFIG += debug plugin

debug:DEFINES += __DEBUG__
DESTDIR = ../plugins/

OTHER_FILES += \
    parser/sexp/sexpXP.a

