INCLUDEPATH += ./parser \
    ./parser/sexp
win32:LIBS += ./parser/sexp/sexpXP.a
else:LIBS += ./parser/sexp/sexp.a

SOURCES += *.cpp
SOURCES -= moc_*.cpp

HEADERS += *.h\
	*.hpp

CONFIG += debug
QT += opengl
SUBDIRS += parser
