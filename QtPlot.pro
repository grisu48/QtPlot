#-------------------------------------------------
#
# Project created by QtCreator 2017-07-26T09:19:21
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtPlot
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        qcustomplot.cpp \
    plot.cpp \
    fileparser.cpp

HEADERS  += mainwindow.h \
        qcustomplot.h \
    plot.h \
    fileparser.h

FORMS    += mainwindow.ui
