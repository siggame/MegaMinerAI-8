INCLUDEPATH += ../interfaces \
  ../parser \
  ../parser/sexp \
  ../lib/ \
  ../common/
DEPENDPATH += ../common/
win32:LIBS += ./parser/sexp/sexpXP.a
else:LIBS += ./parser/sexp/sexp.a
MOC = moc
TEMPLATE = lib
TARGET = bloom 
SOURCES += *.cpp \
  ./parser/*.cpp
  
HEADERS += bloom.h

QMAKE_CFLAGS_DEBUG += -pg
QMAKE_CXXFLAGS_DEBUG += -pg
QMAKE_LFLAGS_DEBUG += -pg
CONFIG += debug plugin
QT += opengl

debug:DEFINES += __DEBUG__
DESTDIR = ../plugins/
