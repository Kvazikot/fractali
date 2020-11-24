QT       += core gui widgets
QT += opengl

TARGET = livegpu
TEMPLATE = app
LIBS+="C:\Program Files (x86)\Windows Kits\8.1\Lib\winv6.3\um\x64\OpenGL32.Lib"
#LIBS+="C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A\Lib\OpenGL32.Lib"
LIBS+="..\OpenGL32.Lib"
SOURCES += main.cpp \
    cellularautomatas.cpp \
    quadsprite.cpp \
    livewiget.cpp
HEADERS += \
    cellularautomatas.h \
    quadsprite.h \
    livewidget.h

RESOURCES += \
        shaders.qrc \
        textures.qrc
