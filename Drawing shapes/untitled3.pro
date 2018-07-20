#-------------------------------------------------
#
# Project created by QtCreator 2016-11-18T18:31:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled3
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    moveitem.cpp

HEADERS  += widget.h \
    moveitem.h

FORMS    += widget.ui



unix: LIBS += -L$$PWD/../figures/ -lfigures.1.0.0

INCLUDEPATH += $$PWD/../figures
DEPENDPATH += $$PWD/../figures
