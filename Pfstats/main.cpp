#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <stdio.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QDesktopWidget dw;

    printf("teste");

    //int x = dw.width();
    //int y = dw.height();

    //w.setFixedSize(x,y);
    w.startStacked();

    w.show();

    return a.exec();
}
