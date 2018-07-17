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
           dialog.cpp \
           dialogshapemodel.cpp \
           cam.cpp  \
    nouse.cpp \
    aqdata.cpp \
    aqlog.cpp \
    inifile.cpp \
    tcpip.cpp

HEADERS  += mainwindow.h \
            halfunc.h \
            dialog.h \
            dialogshapemodel.h \
            cam.h \
    aqdata.h \
    aqlog.h \
    inifile.h \
    tcpip.h

FORMS    += mainwindow.ui \
            dialog.ui \
            dialogshapemodel.ui

INCLUDEPATH += E:\QtPath\hal\inc\

INCLUDEPATH += E:\QtPath\basler\include\

LIBS        += -L$$quote(E:\QtPath\hal\lib\x64-win64) \
               -lhalcon \
               -lhalconcpp10 \
               -lhalconcpp

LIBS        += -L$$quote(E:\QtPath\basler\lib\x64) \

RESOURCES += aqlogo.qrc
