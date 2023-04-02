#include "mainwindow.h"
#include "startwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //old, test window
    MainWindow testw;
    testw.show();

    StartWindow w;
    w.show();

    return a.exec();
}
