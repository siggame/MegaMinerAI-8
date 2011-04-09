INCLUDEPATH += ./lib/parser \
    ./lib/parser/sexp
win32:LIBS += ./lib/parser/sexp/sexpXP.a
else:LIBS += ./lib/parser/sexp/sexp.a

PPATHS +=./lib/gameobject/\
		./lib/manager/\
		./lib/mutex/\
		./lib/threadler/\
		./lib/optionsmanager/\
		./lib/renderer/\
		./lib/resourcemanager/\
		./lib/timemanager/\
		./lib/gameobject/\
    ./lib/gui/\
    ./lib/parser/


SOURCES += main.cpp\
  ./lib/gameobject/*.cpp\
  ./lib/mutex/*.cpp\
  ./lib/threadler/*.cpp\
  ./lib/optionsmanager/*.cpp\
  ./lib/renderer/*.cpp\
  ./lib/renderer/lookupTable/*.cpp\
  ./lib/gui/*.cpp\
  ./lib/timemanager/*.cpp\
  ./lib/parser/parser.cpp\
  ./lib/parser/structures.cpp\
  ./lib/*.cpp\
  ./lib/resourcemanager/*.cpp\
  ./piracy/*.cpp

MOC = moc

HEADERS += *.h\
  ./lib/manager/*.h\
  ./lib/timemanager/*.h\
  ./lib/gameobject/*.h\
  ./lib/mutex/*.h\
  ./lib/threadler/*.h\
  ./lib/optionsmanager/*.h\
  ./lib/renderer/*.h\
  ./lib/renderer/lookupTable/*.h\
  ./lib/parser/*.h\
  ./lib/gui/*.h\
  ./piracy/*.h


CONFIG += debug
QT += opengl
SUBDIRS += parser tools
