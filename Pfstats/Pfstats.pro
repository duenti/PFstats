#-------------------------------------------------
#
# Project created by QtCreator 2015-03-30T14:31:47
#
#-------------------------------------------------

QT       += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Pfstats
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    inputpfam.cpp

HEADERS  += mainwindow.h \
    inputpfam.h

FORMS    += mainwindow.ui \
    inputpfam.ui
