#include "mainwindow.h"
#include <QApplication>

QSound *sound= new QSound(":/backmusic2.wav");

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    sound->setLoops(100);
    sound->play();
    w.show();
    return a.exec();
}
