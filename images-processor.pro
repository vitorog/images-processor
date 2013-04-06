#-------------------------------------------------
#
# Project created by QtCreator 2013-04-05T23:04:08
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = images-processor
TEMPLATE = app

INCLUDEPATH += /media/Vitor/Development/Projects/Github/shade-framework

LIBS += -lGLEW -lGL -lGLU

SOURCES += main.cpp\
        main_window.cpp \
    gl_widget.cpp



HEADERS  += main_window.h \
    gl_widget.h


FORMS    += main_window.ui

unix:!macx: LIBS += -L$$PWD/../../shade-framework-build/ -lshade-framework

INCLUDEPATH += $$PWD/../../shade-framework-build
DEPENDPATH += $$PWD/../../shade-framework-build

unix:!macx: PRE_TARGETDEPS += $$PWD/../../shade-framework-build/libshade-framework.a
