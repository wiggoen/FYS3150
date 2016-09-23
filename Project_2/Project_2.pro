TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    potential.cpp \
    system.cpp \
    unit_test.cpp

HEADERS += \
    potential.h \
    system.h \
    catch.hpp \
    unit_test.h

INCLUDEPATH += /usr/local/include

LIBS += -L/usr/local/lib -larmadillo -llapack -lblas
