#-------------------------------------------------
#
# Project created by QtCreator 2015-03-30T14:31:47
#
#-------------------------------------------------

QT       += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Pfstats
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    alignment.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    alignment.h

FORMS    += mainwindow.ui
