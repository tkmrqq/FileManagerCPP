#include "mainwindow.h"
#include "fileinfolist.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDir>
#include <QLayout>
#include <QMouseEvent>
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

    contextMenu->setStyleSheet("background-color:#FFFFFF; border-radius: 30px;"
                               " color: white; QMenu:hover {color: black}");
    //dirmodel
    QString startPath = QDir::rootPath();
    QStringList args = QApplication::arguments();

    if (args.count() > 1) {
        startPath = args.at(1);
        if (startPath == ".") {
            startPath = getenv("PWD");
        } else if (QUrl(startPath).isLocalFile()) {
            startPath = QUrl(args.at(1)).toLocalFile();
        }
    }

    renderDir(startPath);
    //    getDriveList();

    //path change
    fileSystemWatcher = new QFileSystemWatcher(this);
    connect(fileSystemWatcher,
            &QFileSystemWatcher::directoryChanged,
            this,
            &MainWindow::onDirectoryChanged);

    //prev dir handle
    connect(ui->backButton, &QPushButton::clicked, this, &MainWindow::on_backButton_clicked);
    //favourites and disks handlers
    connect(ui->Desktop, &QPushButton::clicked, this, &MainWindow::to_desktop);

    connect(ui->Disk1, &QPushButton::clicked, this, &MainWindow::to_disk);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//window buttons actions
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

void MainWindow::on_backButton_clicked()
{
    QDir currPath = ui->pathLabel->text();
    //    qDebug() << "Old path = " << currPath;

    currPath.cdUp();
    QString newPath = currPath.path();
    //    qDebug() << "New Path = " << newPath << "Old path changed = " << currPath << "\n";
    clearDir();
    renderDir(newPath);
}

void MainWindow::onButtonClicked(QString folderName)
{
    // Запускаем таймер для ожидания второго щелчка
    doubleClickTimer->start(QApplication::doubleClickInterval());
    qDebug() << folderName;
    clearDir();
    renderDir(folderName);
}

// Слот для обработки двойного щелчка
void MainWindow::handleDoubleClick(QString folderPath)
{
    qDebug() << "Folder path in hanlde: " << folderPath;
    //    clearDir();
    //    renderDir(folderPath);
}

void MainWindow::onDirectoryChanged()
{
    clearDir();
    QString currDir = QDir::currentPath();
    renderDir(currDir);
}

void MainWindow::renderDir(const QString &dirPath)
{
    ui->pathLabel->setText(dirPath);
    QDir directory(dirPath);
    QStringList files = directory.entryList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Files);

    //    qDebug() << directory;
    //    qDebug() << "File in dir: " << files;
    foreach (const QString &filename, files) {
        // Создаем кнопку
        QPushButton *button = new QPushButton;
        button->setIcon(
            QIcon(":/new/windowIcon/Resources/Icons/folder.svg")); // Устанавливаем иконку
        button->setIconSize(QSize(64, 64)); // Устанавливаем размер иконки

        //        connect(button, &QPushButton::clicked, this, &MainWindow::onButtonClicked);

        // Создаем QLabel для имени файла
        QLabel *label = new QLabel(QFileInfo(filename).fileName());
        label->setWordWrap(true); // Перенос по словам
        label->setMaximumWidth(64);

        //double click handle
        doubleClickTimer = new QTimer(this);
        doubleClickTimer->setSingleShot(true);
        doubleClickTimer->setInterval(QApplication::doubleClickInterval());
        //        connect(doubleClickTimer, &QTimer::timeout, this, &MainWindow::handleDoubleClick);

        QString folderPath = dirPath + '/' + filename;

        QString transPath = dirPath + '/'
                            + QFileInfo(filename).filePath(); //путь для переходу в папку

        connect(button, &QPushButton::clicked, [=]() {
            //            QString folderPath = filename;
            MainWindow::onButtonClicked(transPath);
        });

        connect(doubleClickTimer, &QTimer::timeout, [=]() {
            MainWindow::handleDoubleClick(transPath);
        });

        // Создаем вертикальный макет для размещения кнопки и подписи
        QVBoxLayout *buttonLayout = new QVBoxLayout;
        buttonLayout->addWidget(button);
        buttonLayout->addWidget(label);
        // Создаем виджет-контейнер для вертикального макета
        QWidget *buttonContainer = new QWidget;
        buttonContainer->setLayout(buttonLayout);

        //styles
        label->setStyleSheet("color: white");
        button->setStyleSheet("background-color: transparent");
        // Добавляем виджет-контейнер в основной вертикальный макет (foldersFrame)
        ui->foldersFrame->layout()->addWidget(buttonContainer);
    }
    ui->foldersFrame->layout()->setAlignment(Qt::AlignTop);
}

void MainWindow::clearDir()
{
    QLayout *layout = ui->foldersFrame->layout();
    QLayoutItem *item;
    while ((item = layout->takeAt(0)) != nullptr) {
        QWidget *widget = item->widget();
        if (widget != nullptr) {
            delete widget;
        }
        delete item;
    }
}

//folders model

//favourites button hadles

void MainWindow::to_desktop()
{
    clearDir();
    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    renderDir(desktopPath);
}

void MainWindow::to_disk()
{
    QStringList drives;
    foreach (const QFileInfo &drive, QDir::drives()) {
        drives << drive.absolutePath();
    }
    clearDir();
    renderDir(drives[1]);
}

void MainWindow::getDriveList()
{
    QStringList drives;
    foreach (const QFileInfo &drive, QDir::drives()) {
        drives << drive.absolutePath();
    }
    foreach (const QString &diskName, drives) {
        QPushButton *button = new QPushButton(diskName);
        //        connect(button, &QPushButton::clicked, this, [this, diskName]() { to_disk(diskName); });
        // Добавляйте кнопку в ваш интерфейс
        ui->frame_4->layout()->addWidget(button);
    }
}
