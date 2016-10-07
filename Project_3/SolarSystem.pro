TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
#DEFINES += CATCH_CONFIG_MAIN # uncomment this when using unit_test.cpp. Remember to rebuild when uncommenting and commenting!

SOURCES += main.cpp \
    celestialbody.cpp \
    solarsystem.cpp \
    vec3.cpp \
    euler.cpp \
    unit_test.cpp \
    verlet.cpp

HEADERS += \
    celestialbody.h \
    solarsystem.h \
    vec3.h \
    euler.h \
    catch.hpp \
    verlet.h

