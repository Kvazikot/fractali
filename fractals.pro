#-------------------------------------------------
#
# Project created by QtCreator 2014-09-24T10:08:15
#
#-------------------------------------------------

QT       += core gui
QT += concurrent
QT += widgets opengl
#QMAKE_CXXFLAGS+=-std=c++11
INCLUDEPATH+="C:\Program Files\Windows Kits\8.0\Include\um"
INCLUDEPATH+="C:\Program Files\Windows Kits\8.0\Include\shared"
TARGET = fractalsEXE
TEMPLATE = app
CONFIG += warn_off

SOURCES += main.cpp\
        mainwindow.cpp \
    fractals.cpp \
    print.cpp \
    fit_rects.cpp \
    lsystem.cpp \
    quadsprite.cpp \
    livewiget.cpp \
    cellularautomatas.cpp

HEADERS  += mainwindow.h \
    fractals.h \
    quadsprite.h \
    livewidget.h \
    fit_rects.h \
    print.h \
    lsystem.h \
    cellularautomatas.h


FORMS    += mainwindow.ui \
    fractals.ui

RESOURCES += \
        shaders.qrc \
        textures.qrc
