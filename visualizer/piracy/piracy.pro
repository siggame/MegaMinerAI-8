INCLUDEPATH += ../interfaces \
  ../parser \
  ../parser/sexp \
  ../lib/
win32:LIBS += ../lib/parser/sexp/sexpXP.a
else:LIBS += ../lib/parser/sexp/sexp.a
MOC = moc
TEMPLATE = lib
TARGET = piracy
SOURCES += piracy.cpp
HEADERS += *.h

QMAKE_CFLAGS_DEBUG += -pg
QMAKE_CXXFLAGS_DEBUG += -pg
QMAKE_LFLAGS_DEBUG += -pg
CONFIG += debug plugin
QT += opengl

debug:DEFINES += __DEBUG__
DESTDIR = ../plugins/
