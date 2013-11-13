TEMPLATE = app
DEPENDPATH += .
INCLUDEPATH += . ../../

CONFIG += warn_on
CONFIG += debug

TARGET = qt_thread

QT += xml network


# Input
HEADERS += testclient.h
FORMS += testclient.ui
SOURCES += main.cpp testclient.cpp

unix { 
    CONFIG(debug, debug|release) {
        #LIBS += ../../libqxmlrpc_debug.a
        #LIBS += ../../libqxmlrpc.a
        LIBS += -lqxmlrpc

    } else {
        LIBS += ../../libqxmlrpc.a
    }
}

win32:LIBS += ../../xmlrpc/qxmlrpc.lib

