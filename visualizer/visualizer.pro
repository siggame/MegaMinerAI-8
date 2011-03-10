INCLUDEPATH += ./parser \
    ./parser/sexp
win32:LIBS += ./parser/sexp/sexpXP.a
else:LIBS += ./parser/sexp/sexp.a

LPATHS +=./lib/gameobject/\
		./lib/manager/\
		./lib/mutex/\
		./lib/threadler/\
		./lib/optionsmanager/\
		./lib/renderer/\
		./lib/timemanager/\
		./lib/gameobject/\
		./oldstuff/


SOURCES += *.cpp\
			$$LPATHS/*.cpp

SOURCES -= moc_*.cpp

HEADERS += *.h\
	*.hpp

CONFIG += debug
QT += opengl
SUBDIRS += parser
