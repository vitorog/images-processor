#-------------------------------------------------
#
# Project created by QtCreator 2013-04-05T23:04:08
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = images-processor
TEMPLATE = app

INCLUDEPATH += ../shade-framework
INCLUDEPATH += /home/vitor/glm/glm-0.9.5.2/glm

LIBS += -lGLEW -lGL -lGLU -lopencv_core -lopencv_highgui -lopencv_imgproc

SOURCES += main.cpp\
        main_window.cpp \    
    image_renderer.cpp \
    webcam_reader.cpp

HEADERS  += main_window.h \    
    image_renderer.h \
    webcam_reader.h

FORMS    += main_window.ui

OTHER_FILES += \
    basic.vert \
    basic.frag \
    negative.frag \
    blur.frag \
    sobel.frag

unix:!macx: LIBS += -L$$PWD/../Builds/shade-framework-build/ -lshade-framework

INCLUDEPATH += $$PWD/../Builds/shade-framework-build
DEPENDPATH += $$PWD/../Builds/shade-framework-build
