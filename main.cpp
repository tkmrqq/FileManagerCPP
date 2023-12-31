#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QMainWindow>
#include <QPushButton>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPalette palette = a.palette();
    palette.setColor(QPalette::WindowText, Qt::white);
    a.setPalette(palette);

    QFile styleFile(":/style/styles.qss");
    styleFile.open(QFile::ReadOnly);
    QString style = QLatin1String(styleFile.readAll());
    a.setStyleSheet(style);

    MainWindow w;
    //    w.resize(2000, 1000);
    w.show();
    return a.exec();
}

