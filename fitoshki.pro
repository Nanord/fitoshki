#-------------------------------------------------
#
# Project created by QtCreator 2017-02-13T19:20:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fitoshki
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    field.cpp \
    winorlose.cpp

HEADERS  += mainwindow.h \
    field.h \
    winorlose.h

FORMS    += mainwindow.ui \
    winorlose.ui
