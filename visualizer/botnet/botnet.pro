INCLUDEPATH += ../interfaces \
  ../parser \
  ../parser/sexp \
  ../lib/ \
  ../common/
DEPENDPATH += ../common/
MOC = moc
TEMPLATE = lib 
TARGET = botnet 
SOURCES += *.cpp \
  ../common/*.cpp \
  parser/sexp/*.cpp \
  parser/structures.cpp \
  parser/parseGamelog.cpp
  
HEADERS += *.h \
  parser/*.h \
  parser/sexp/*.h \
  ../common/*.h

#QMAKE_CFLAGS_DEBUG += -pg
#QMAKE_CXXFLAGS_DEBUG += -pg
QMAKE_LFLAGS_DEBUG += -shared
QMAKE_LFLAGS_RELEASE += -shared
CONFIG += debug plugin
CONFIG += dll
QT += opengl

#debug:DEFINES += __DEBUG__ 
DEFINES += YY_NO_UNISTD_H
DESTDIR = ../plugins/
