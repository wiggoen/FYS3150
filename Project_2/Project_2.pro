TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    potential.cpp \
    system.cpp

HEADERS += \
    potential.h \
    system.h

INCLUDEPATH += /usr/local/include

LIBS += -L/usr/local/lib -larmadillo -llapack -lblas
