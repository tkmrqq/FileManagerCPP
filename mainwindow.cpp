#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QtCore>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    ui->closeButton->setStyleSheet("QPushButton{background: transparent;}");

    this->setStyleSheet("background-color:#222222");
//    this->setWindowFlag(Qt::FramelessWindowHint);

    //ContextMenu logic
    contextMenu = new QMenu(this);
    contextMenu->setStyleSheet(
        "background-color:#171717; border: 1px solid #171717; border-radius: 30px;");

    QAction *view = contextMenu->addAction("View");
    QAction *sort = contextMenu->addAction("Sort");
    QAction *update = contextMenu->addAction("Update");
    QAction *create = contextMenu->addAction("Create");
    QAction *properties = contextMenu->addAction("Properties");

    connect(view, &QAction::triggered, this, &MainWindow::action1Clicked);
    connect(sort, &QAction::triggered, this, &MainWindow::action2Clicked);
    connect(update, &QAction::triggered, this, &MainWindow::action2Clicked);
    connect(create, &QAction::triggered, this, &MainWindow::action2Clicked);
    connect(properties, &QAction::triggered, this, &MainWindow::action2Clicked);

    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QWidget::customContextMenuRequested, this, &MainWindow::showContextMenu);

    //dirmodel
    QString sPath = "C:/";
    dirmodel = new QFileSystemModel(this);
    dirmodel->setRootPath(sPath);
    //    ui->treeView->setModel(dirmodel);

    //file model

    QString rootPath = "C:/";
    QDir rootDir(rootPath);

    QFileInfoList fileList = rootDir.entryInfoList();

    QTableWidget layout(this);

    foreach (QFileInfo fileInfo, fileList) {
        QIcon icon = QFileIconProvider().icon(fileInfo);
        QLabel *label = new QLabel;
        label->setPixmap(icon.pixmap(48, 48));
        label->setText(fileInfo.fileName());
    }
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
