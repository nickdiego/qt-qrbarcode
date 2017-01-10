#include <QtGui/QGuiApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
