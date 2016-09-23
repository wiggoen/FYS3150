TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
DEFINES += CATCH_CONFIG_MAIN

SOURCES += main.cpp \
    potential.cpp \
    system.cpp \
    unit_test.cpp

HEADERS += \
    potential.h \
    system.h \
    catch.hpp

INCLUDEPATH += /usr/local/include

LIBS += -L/usr/local/lib -larmadillo -llapack -lblas
