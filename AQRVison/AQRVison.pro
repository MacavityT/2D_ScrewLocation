#-------------------------------------------------
#
# Project created by QtCreator 2018-04-30T13:44:47
#
#-------------------------------------------------

QT += core gui
QT += network
QT += core
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AQRVison

TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp\
           mainwindow.cpp \
           halfunc.cpp \
           dialogshapemodel.cpp \
           cam.cpp  \
    aqdata.cpp \
    aqlog.cpp \
    inifile.cpp \
    modbus_tcp_server.cpp \
    mythreads.cpp \
    dialogcalibration.cpp

HEADERS  += mainwindow.h \
            halfunc.h \
            dialogshapemodel.h \
            cam.h \
    aqdata.h \
    aqlog.h \
    inifile.h \
    modbus_tcp_server.h \
    mythreads.h \
    dialogcalibration.h

FORMS    += mainwindow.ui \
            dialogshapemodel.ui \
    dialogcalibration.ui

INCLUDEPATH += "D:/Program Files/MVTec/HALCON-13.0/include/"

INCLUDEPATH += "D:/Program Files/Basler/pylon 5/Development/include/"

LIBS        += -L$$quote(D:\Program Files\MVTec\HALCON-13.0\lib\x64-win64) \
               -lhalcon \
               -lhalconcpp10 \
               -lhalconcpp

LIBS        += -L$$quote(D:\Program Files\Basler\pylon 5\Development\lib\x64) \

RESOURCES += aqlogo.qrc

QT += serialport serialbus

CONFIG += c++11
