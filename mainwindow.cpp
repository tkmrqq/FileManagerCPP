#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenuBar>
#include <QtCore>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    ui->closeButton->setStyleSheet("QPushButton{background: transparent;}");

    this->setStyleSheet("background-color:#222222");
    this->setWindowFlag(Qt::FramelessWindowHint);

    //ContextMenu logic
    contextMenu = new QMenu(this);
    contextMenu->setStyleSheet("background-color:#171717");

    QAction *action1 = contextMenu->addAction("Move 1");
    QAction *action2 = contextMenu->addAction("Move 2");

    connect(action1, &QAction::triggered, this, &MainWindow::action1Clicked);
    connect(action2, &QAction::triggered, this, &MainWindow::action2Clicked);

    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QWidget::customContextMenuRequested, this, &MainWindow::showContextMenu);

    //dirmodel

    QString sPath = "C:/";
    dirmodel = new QFileSystemModel(this);
    dirmodel->setRootPath(sPath);
    ui->treeView->setModel(dirmodel);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_closeButton_clicked()
{
    QApplication::activeWindow()->close();
}

void MainWindow::on_maximizeButton_clicked(){
    bool isMaximized = false;
    if(isMaximized){
        QApplication::activeWindow()->showNormal();
    }
    else {
        QApplication::activeWindow()->showMaximized();
        isMaximized = true;
    }
    isMaximized = !isMaximized;
}

void MainWindow::on_minimizeButton_clicked(){
    QApplication::activeWindow()->showMinimized();
}
