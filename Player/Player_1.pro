#-------------------------------------------------
#
# Project created by QtCreator 2018-07-20T16:38:42
#
#-------------------------------------------------

QT       += core gui
QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Player_1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    soundplayer.cpp

HEADERS  += mainwindow.h \
    soundplayer.h

FORMS    += mainwindow.ui
