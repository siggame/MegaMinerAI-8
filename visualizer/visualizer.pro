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
		./lib/gameobject/


SOURCES += *.cpp\
  ./lib/gameobject/*.cpp\
  ./lib/mutex/*.cpp\
  ./lib/threadler/*.cpp\
  ./lib/optionsmanager/*.cpp\
  ./lib/renderer/*.cpp\
  ./lib/gameobject/*.cpp



HEADERS += *.h\
  ./lib/manager/*.h\
  ./lib/timemanager/*.h

CONFIG += debug
QT += opengl
SUBDIRS += parser
