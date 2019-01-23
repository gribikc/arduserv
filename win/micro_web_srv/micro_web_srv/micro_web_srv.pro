QT += core
QT -= gui

QT       += serialport
QT += network

CONFIG += c++11

TARGET = micro_web_srv
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    gr_serial/gr_serial.cpp \
    gr_sock_srv/gr_sock_srv.cpp

HEADERS += \
    gr_serial/gr_serial.h \
    gr_sock_srv/gr_sock_srv.h
