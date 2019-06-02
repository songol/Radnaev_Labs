#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    //w.drawMyFuncion(-100, 100);
    w.show();

    return a.exec();
}
