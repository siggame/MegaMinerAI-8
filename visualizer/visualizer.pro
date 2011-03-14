INCLUDEPATH += ./lib/parser \
    ./lib/parser/sexp
win32:LIBS += ./lib/parser/sexp/sexpXP.a
else:LIBS += ./lib/parser/sexp/sexp.a

MOC_DIR = moc

PPATHS +=./lib/gameobject/\
		./lib/manager/\
		./lib/mutex/\
		./lib/threadler/\
		./lib/optionsmanager/\
		./lib/renderer/\
		./lib/timemanager/\
		./lib/gameobject/\
		./oldstuff/


SOURCES += *.cpp

HEADERS += *.h\
  $$PPATHS/*.h


CONFIG += debug
QT += opengl
SUBDIRS += parser
