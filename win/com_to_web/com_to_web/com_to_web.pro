#-------------------------------------------------
#
# Project created by QtCreator 2019-02-23T12:42:26
#
#-------------------------------------------------

QT       += core gui
QT       += serialport
QT       += network
QT       += bluetooth

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = com_to_web
TEMPLATE = app


SOURCES += main.cpp\
        com_to_web.cpp\
    gr_serial/gr_serial.cpp \
    gr_bluetooth/gr_bluetooth.cpp


HEADERS  += com_to_web.h\
    gr_serial/gr_serial.h \
    gr_bluetooth/gr_bluetooth.h

FORMS    += com_to_web.ui

DISTFILES +=  AndroidManifest.xml

CONFIG += mobility
MOBILITY = 

