# #####################################################################
# Automatically generated by qmake (2.01a) Mon Mar 29 13:43:34 2010
# #####################################################################
TEMPLATE = app
TARGET = q4weather
DEPENDPATH += . \
    src \
    src/engine \
    src/gui
INCLUDEPATH += . \
    src/gui
QT += xml \
    network
OBJECTS_DIR = .obj
MOC_DIR = .moc

# Input
HEADERS += src/engine/weather.h \
    src/engine/location.h \
    src/engine/engine.h \
    src/engine/yahooeng.h \
    src/engine/googleeng.h \
    src/gui/mainwindow.h
SOURCES += src/main.cpp \
    src/gui/mainwindow.cpp \
    src/engine/yahooeng.cpp \
    src/engine/googleeng.cpp
RESOURCES += q4weather.qrc