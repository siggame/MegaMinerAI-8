INCLUDEPATH += ../interfaces \
 ../parser \
 ../parser/sexp \
 ../common/ 

DEPENDPATH += ../common/ 

win32:LIBS += ./parser/sexp/sexpXP.a
else:LIBS += ./parser/sexp/sexp.a

TEMPLATE = lib
TARGET =  bloom 
SOURCES = *.cpp \
  ./parser/*.cpp
HEADERS += *.h

CONFIG += debug plugin
debug:DEFINES += __DEBUG__

DESTDIR = ../plugins/
