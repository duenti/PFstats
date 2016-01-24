#-------------------------------------------------
#
# Project created by QtCreator 2015-03-30T14:31:47
#
#-------------------------------------------------
#
#COLOCAR O DIRETORIO ABOR NA PASTA RAIZ INSTALADA
##NO WINDOWS libpath DEVE COMEÇAR COM VALOR DO DIR RAIZ

QT       += core gui webkitwidgets
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Pfstats
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXXFLAGS += -fopenmp
#LIBS +=-lstdc++\
#    libQt5PrintSupport.so.5

LIBS += -fopenmp

SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    alignment.cpp \
    about.cpp \
    uniprot.cpp \
    feature.cpp \
    pdb.cpp \
    pdbatom.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    alignment.h \
    about.h \
    uniprot.h \
    feature.h \
    pdb.h \
    pdbatom.h

FORMS    += mainwindow.ui \
    about.ui
