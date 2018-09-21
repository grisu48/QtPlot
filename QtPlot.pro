#-------------------------------------------------
#
# Project created by QtCreator 2017-07-26T09:19:21
#
#-------------------------------------------------

QT       += core gui printsupport

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtPlot
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        qcustomplot.cpp \
    plot.cpp \
    fileparser.cpp \
    dialogimage.cpp

HEADERS  += mainwindow.h \
        qcustomplot.h \
    plot.h \
    fileparser.h \
    dialogimage.h

FORMS    += mainwindow.ui \
    dialogimage.ui

RESOURCES += \
    resources.qrc
