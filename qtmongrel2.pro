#-------------------------------------------------
#
# Project created by QtCreator 2012-02-27T19:14:13
#
#-------------------------------------------------

QT       += core

QT       -= gui
QT       -= webkit

TARGET = qtmongrel2
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += src/main.cpp \
    src/qtnetstring/QTNetString.cpp \
    src/zeromqt/ZmqSocket.cc \
    src/zeromqt/ZmqContext.cc \
    src/Mongrel2.cpp \
    src/Request.cpp \
    src/Response.cpp

HEADERS += \
    src/main.h \
    src/qtnetstring/QTNetString.h \
    src/zeromqt/ZmqMessage.h \
    src/zeromqt/ZmqException.h \
    src/zeromqt/ZmqContext.h \
    src/zeromqt/ZmqSocket.h \
    src/Mongrel2.h \
    src/Request.h \
    src/Response.h

LIBS += -lzmq
