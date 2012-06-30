#-------------------------------------------------
#
# Project created by QtCreator 2012-06-29T20:03:42
#
#-------------------------------------------------

QT       += core gui

TARGET = mooScreenGrabber
TEMPLATE = app

SOURCES += main.cpp\
        mainwidget.cpp \
    grabberthread.cpp

HEADERS  += mainwidget.h \
    common.h \
    grabberthread.h

FORMS    += mainwidget.ui

unix: LIBS += -lX11 -lXfixes
