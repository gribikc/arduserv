#-------------------------------------------------
#
# Project created by QtCreator 2019-02-23T12:42:26
#
#-------------------------------------------------
QT       += core gui
QT       -= gui
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


SOURCES +=  main.cpp\
            com_to_web.cpp\
            gr_data_source/gr_data_source.cpp\
    gr_logger/gr_logger.cpp \
    gr_sensor/gr_sensor.cpp \
            gr_serial/gr_serial.cpp \
            gr_bluetooth/gr_bluetooth.cpp \
            gr_gps/gr_gps.cpp \
    gr_http_client/gr_http_client.cpp \
    gr_dev_manager/gr_dev_manager.cpp \
    gr_tcp_client/gr_tcp_client.cpp \
    gr_udp_client/gr_udp_client.cpp

HEADERS  += com_to_web.h\
    file_system.h \
            gr_data_source/gr_data_source.h\
    gr_logger/gr_logger.h \
    gr_sensor/gr_sensor.h \
            gr_serial/gr_serial.h \
            gr_bluetooth/gr_bluetooth.h\
            gr_gps/gr_gps.h \
    gr_http_client/gr_http_client.h \
    gr_dev_manager/gr_dev_manager.h \
    gr_tcp_client/gr_tcp_client.h \
    gr_udp_client/gr_udp_client.h

FORMS    += com_to_web.ui

#DISTFILES += \
#    android/AndroidManifest.xml \
#    android/gradle/wrapper/gradle-wrapper.jar \
#    android/gradlew \
#    android/res/values/libs.xml \
#    android/build.gradle \
#    android/gradle/wrapper/gradle-wrapper.properties \
#    android/gradlew.bat

CONFIG += mobility
MOBILITY = 

#!!!ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android!!!#

MOBILITY += sensors

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

android {
    QMAKE_LFLAGS += -nostdlib++
}

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}

