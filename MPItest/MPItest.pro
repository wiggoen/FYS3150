TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

INCLUDEPATH += /usr/local/Cellar/open-mpi/2.0.1/include
LIBS += -L/usr/local/opt/libevent/lib -L/usr/local/Cellar/open-mpi/2.0.1/lib -lmpi
