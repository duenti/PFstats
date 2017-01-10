#include "mainwindow.h"
#include "omp.h"
#include <QApplication>
#include <QDesktopWidget>
#include <stdio.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //QDesktopWidget dw;
//#pragma omp parallel for
    //for(int i = 0; i < 1000000; i++){
        //printf("%d\n",i);
    //}
    //int x = dw.width();
    //int y = dw.height();

    //w.setFixedSize(x,y);

    w.startStacked();

    w.show();

    return a.exec();
}
