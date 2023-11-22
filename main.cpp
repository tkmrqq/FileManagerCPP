#include "mainwindow.h"

#include <QApplication>
#include <QMainWindow>
#include <QPushButton>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPalette palette = a.palette();

    palette.setColor(QPalette::WindowText, Qt::white);
    a.setPalette(palette);

    MainWindow w;
    //    w.resize(2000, 1000);
    w.show();
    return a.exec();
}

