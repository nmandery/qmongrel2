QT       += core

QT       -= gui
QT       -= webkit

TARGET = qmongrel2_example
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    example.cpp \
    src/qtnetstring/QTNetString.cpp \
    src/zeromqt/ZmqSocket.cc \
    src/zeromqt/ZmqContext.cc \
    src/Mongrel2.cpp \
    src/Request.cpp \
    src/Response.cpp

HEADERS += \
    example.h \
    src/qtnetstring/QTNetString.h \
    src/zeromqt/ZmqMessage.h \
    src/zeromqt/ZmqException.h \
    src/zeromqt/ZmqContext.h \
    src/zeromqt/ZmqSocket.h \
    src/Mongrel2.h \
    src/Request.h \
    src/Response.h

LIBS += -lzmq
