INCLUDEPATH += ../interfaces \  # INCLUDEPATH tells the compiler where to find our
  ../parser \                   # header files for this project.
  ../parser/sexp \              # interfaces is the code to join the plugin to the core
  ../common/                    # parser is self-explanatory. Common contains code common 
                                # to the visualizer core and plugins
DEPENDPATH += ../common/        # DEPENDPATH are the files that we want to check in addition
                                # to those that we are writing now for changes to see
                                # if we need to recompile
win32:LIBS += ./parser/sexp/sexpXP.a
else:LIBS += ./parser/sexp/sexp.a # This is just hooking bloom up to the parser
TEMPLATE = lib      # Tells the compiler that this is a library and not a standalone program
TARGET = bloom      # Tells the compiler that were naming this plugin "bloom"
SOURCES += *.cpp \  # What are the cpp files for this plugin
  ./parser/*.cpp
  
HEADERS += *.h  # What are the header files for this plugin

# These tell the compiler that were going to compile and link with profiling 
# and debugging symbols.  These help us out when the visualizer is going really slow
# or something is going really wrong.
QMAKE_CFLAGS_DEBUG += -pg    
QMAKE_CXXFLAGS_DEBUG += -pg
QMAKE_LFLAGS_DEBUG += -pg
CONFIG += debug plugin    # Tells the compiler that this is going to be a debug build
                          # and a plugin

debug:DEFINES += __DEBUG__  # This constant will be available when were in a debug build.
DESTDIR = ../plugins/       # Where to put the plugin on a successful build.


