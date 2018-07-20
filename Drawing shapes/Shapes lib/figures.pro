#-------------------------------------------------
#
# Project created by QtCreator 2016-10-04T22:35:17
#
#-------------------------------------------------

QT       -= gui

TARGET = figures
TEMPLATE = lib

DEFINES += FIGURES_LIBRARY

SOURCES += figures.cpp

HEADERS += figures.h\
        figures_global.h
CONFIG += build_all
unix {
    target.path = /usr/lib
    INSTALLS += target
}
