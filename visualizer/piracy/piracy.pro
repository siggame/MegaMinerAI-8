INCLUDEPATH += ../interfaces \
  ../parser \
  ../parser/sexp \
  ../lib/ \
  ../common/
DEPENDPATH += ../common/
MOC = moc
TEMPLATE = lib
TARGET = piracy
SOURCES += piracy.cpp \
  animations.cpp \
  piracyStack.cpp \
  piratemap.cpp \
  ../common/*.cpp \
  parser/sexp/*.cpp \
  parser/structures.cpp \
  parser/parseGamelog.cpp
  
HEADERS += *.h \
  parser/*.h \
  parser/sexp/*.h \
  ../common/*.h

QMAKE_CFLAGS_DEBUG += -pg
QMAKE_CXXFLAGS_DEBUG += -pg
QMAKE_LFLAGS_DEBUG += -pg
CONFIG += debug plugin
QT += opengl

debug:DEFINES += __DEBUG__
DEFINES += YY_NO_UNISTD_H
DESTDIR = ../plugins/
