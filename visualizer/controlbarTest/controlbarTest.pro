HEADERS += coolslider.h
SOURCES += main.cpp \
gui.cpp \
coolslider.cpp

MOC = moc
QMAKE_CFLAGS_DEBUG += -pg
QMAKE_CXXFLAGS_DEBUG += -pg
QMAKE_LFLAGS_DEBUG += -pg
CONFIG += debug
