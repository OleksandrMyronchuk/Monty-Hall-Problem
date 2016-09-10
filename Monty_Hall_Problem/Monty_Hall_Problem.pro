#-------------------------------------------------
#
# Project created by QtCreator 2016-09-09T19:45:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Monty_Hall_Problem
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    message.cpp \
    addition.cpp

HEADERS  += mainwindow.h \
    message.h \
    addition.h

FORMS    += mainwindow.ui \
    message.ui \
    addition.ui

CONFIG += mobility
MOBILITY = 

RESOURCES += \
    myfile.qrc

