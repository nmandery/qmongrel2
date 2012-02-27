#-------------------------------------------------
#
# Project created by QtCreator 2012-02-27T19:14:13
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = qtmongrel2
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += src/main.cpp \
    src/qtnetstring/qtnetstring.cpp \
    src/zeromqt/ZmqSocket.cc \
    src/zeromqt/ZmqContext.cc

HEADERS += \
    src/qtnetstring/qtnetstring.h \
    src/zeromqt/ZmqMessage.h \
    src/zeromqt/ZmqException.h \
    src/zeromqt/ZmqContext.h \
    src/zeromqt/ZmqSocket.h

LIBS += -lzmq
