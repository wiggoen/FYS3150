TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
#DEFINES += CATCH_CONFIG_MAIN # uncomment this when using unit_test.cpp. Remember to rebuild when uncommenting and commenting!

SOURCES += main.cpp

INCLUDEPATH += /usr/local/include

LIBS += -L/usr/local/lib -larmadillo -llapack -lblas
