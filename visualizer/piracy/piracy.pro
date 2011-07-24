INCLUDEPATH += ../interfaces \
  ../parser \
  ../parser/sexp \
  ../lib/
win32:LIBS += ./parser/sexp/sexpXP.a
else:LIBS += ./parser/sexp/sexp.a
MOC = moc
TEMPLATE = lib
TARGET = piracy
SOURCES += piracy.cpp \
  stacks.cpp \
  parser/*.cpp
  
HEADERS += *.h \
  parser/*.h

QMAKE_CFLAGS_DEBUG += -pg
QMAKE_CXXFLAGS_DEBUG += -pg
QMAKE_LFLAGS_DEBUG += -pg
CONFIG += debug plugin
QT += opengl

debug:DEFINES += __DEBUG__
DESTDIR = ../plugins/
