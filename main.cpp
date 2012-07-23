#include <QtGui/QApplication>
#include "mainwindow.h"
#define EPS 1E-9
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
