INCLUDEPATH += ../interfaces \
  ../parser \
  ../parser/sexp \
  ../common/

DEPENDPATH += ../common/

MOC = moc
TEMPLATE = lib
TARGET = modular
SOURCES += *.cpp ./parser/*.cpp

HEADERS += *.h

QMAKE_CFLAGS_DEBUG += -pg
QMAKE_CXXFLAGS_DEBUG += -pg
QMAKE_LFLAGS_DEBUG += -pg
CONFIG += debug plugin

debug:DEFINES += __DEBUG__
DESTDIR = ../plugins/

