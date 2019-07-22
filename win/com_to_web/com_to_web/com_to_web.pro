#-------------------------------------------------
#
# Project created by QtCreator 2019-02-23T12:42:26
#
#-------------------------------------------------

QT       += core gui
QT       += serialport
QT       += network
QT       += bluetooth
QT       += serialport
QT       += positioning
QT       += sensors
QT       += location

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = com_to_web
TEMPLATE = app


SOURCES += main.cpp\
        com_to_web.cpp\
    gr_serial/gr_serial.cpp \
    gr_bluetooth/gr_bluetooth.cpp \
    gr_gps/gr_gps.cpp



HEADERS  += com_to_web.h\
    gr_serial/gr_serial.h \
    gr_bluetooth/gr_bluetooth.h\
    gr_gps/gr_gps.h

FORMS    += com_to_web.ui

DISTFILES += \ 
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

CONFIG += mobility
MOBILITY = 

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

