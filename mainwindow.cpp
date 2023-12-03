#include "mainwindow.h"
#include "fileinfolist.h"
#include "fileinfowindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDir>
#include <QFileIconProvider>
#include <QInputDialog>
#include <QLayout>
#include <QMouseEvent>
#include <QPalette>
#include <QScrollArea>
#include <QtCore>

void MainWindow::style() {}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //    ui->closeButton->setStyleSheet("QPushButton{background: transparent;}");
    ui->scrollArea->verticalScrollBar()->setStyleSheet(
        "QScrollBar:vertical {"
        "    background: #171717;"
        "    width: 8px;"
        "    border-radius: 4px;"
        "}"
        "QScrollBar::handle:vertical {"
        "    background: #959595;"
        "    border-radius: 4px;"
        "    min-height: 20px;"
        "}"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
        "    background: none;"
        "border"
        "}");
    this->setStyleSheet("background-color:#222222");
    //    this->setWindowFlag(Qt::FramelessWindowHint);

    //ContextMenu logic
    contextMenu = new QMenu(this);
    flowLayout = new FlowLayout;

    QAction *view = contextMenu->addAction("View");
    QAction *sort = contextMenu->addAction("Sort");
    QAction *update = contextMenu->addAction("Update");
    QAction *create = contextMenu->addAction("Create");
    QAction *properties = contextMenu->addAction("Properties");

    connect(view, &QAction::triggered, this, &MainWindow::action1Clicked);
    connect(sort, &QAction::triggered, this, &MainWindow::action2Clicked);
    connect(update, &QAction::triggered, this, &MainWindow::action2Clicked);
    connect(create, &QAction::triggered, this, &MainWindow::actionCreate);
    connect(properties, &QAction::triggered, [=]() { propertiesButton(folderName); });

    setContextMenuPolicy(Qt::CustomContextMenu);

    contextMenu->setStyleSheet("background-color: #FFFFFF; border-radius: 30px;"
                               "color: white;"
                               "QMenu:hover { color: black; }");

    connect(this, &QWidget::customContextMenuRequested, this, &MainWindow::showContextMenu);

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
    //getDriveList();

    //path change
    fileSystemWatcher = new QFileSystemWatcher(this);
    connect(fileSystemWatcher,
            &QFileSystemWatcher::directoryChanged,
            this,
            &MainWindow::onDirectoryChanged);

    //prev dir handle
    //    connect(ui->backButton, &QPushButton::clicked, this, &MainWindow::on_backButton_clicked);
    connect(ui->nextButton, &QPushButton::clicked, this, &MainWindow::on_prevButton_clicked);
    //favourites and disks handlers
    connect(ui->Desktop, &QPushButton::clicked, [=]() {
        to_fav(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation));
    });
    connect(ui->Downloads, &QPushButton::clicked, [=]() {
        to_fav(QStandardPaths::writableLocation(QStandardPaths::DownloadLocation));
    });

    connect(ui->Docs, &QPushButton::clicked, [=]() {
        to_fav(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));
    });

    connect(ui->Music, &QPushButton::clicked, [=]() {
        to_fav(QStandardPaths::writableLocation(QStandardPaths::MusicLocation));
    });

    connect(ui->Video, &QPushButton::clicked, [=]() {
        to_fav(QStandardPaths::writableLocation(QStandardPaths::MoviesLocation));
    });

    connect(ui->Disk1, &QPushButton::clicked, this, &MainWindow::to_disk);

    connect(ui->themeButton, &QPushButton::clicked, this, &MainWindow::on_themeButton_clicked);
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
    QDir currPath = currentPath;
    currPath.cdUp();
    QString newPath = currPath.path();

    qDebug() << "Backbutton: " << newPath;
    if (currentPath != newPath) {
        prevPath = currentPath;
    }
    currentPath = newPath;
    clearDir();
    renderDir(newPath);
}

void MainWindow::on_prevButton_clicked()
{
    clearDir();
    renderDir(prevPath);
}

void MainWindow::onButtonClicked(QString folderName)
{
    // Запускаем таймер для ожидания второго щелчка
    //    doubleClickTimer->start(QApplication::doubleClickInterval());
    QFileInfo fileInfo(folderName);

    if (fileInfo.isDir()) {
        // Это папка - открываем ее
        clearDir();
        currentPath = folderName;
        renderDir(folderName);
    } else if (fileInfo.isFile()) {
        // Это файл - открываем его в соответствующем приложении
        QDesktopServices::openUrl(QUrl::fromLocalFile(folderName));
    }

    qDebug() << folderName;
}

// Слот для обработки двойного щелчка
void MainWindow::handleDoubleClick(QString folderPath)
{
    qDebug() << "Folder path in hanlde: " << folderPath;
    clearDir();
    renderDir(folderPath);
}

void MainWindow::onDirectoryChanged()
{
    clearDir();
    QString currDir = QDir::currentPath();
    renderDir(currDir);
}

//void MainWindow::renderDir(const QString &dirPath)
//{
//    ui->pathLabel->setText(dirPath);
//    currentPath = dirPath;
//    QDir directory(dirPath);
//    QStringList files = directory.entryList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Files);
//    QVBoxLayout *buttonLayout = new QVBoxLayout();

//    foreach (const QString &filename, files) {
//        QPushButton *button = new QPushButton;
//        QFileInfo fileInfo(directory.filePath(filename));
//        QFileIconProvider iconProvider;
//        if (fileInfo.isDir()) {
//            button->setIcon(QIcon(":/new/windowIcon/Resources/Icons/folder.svg"));
//        } else {
//            //            button->setIcon(QIcon(":/new/windowIcon/Resources/Icons/file.svg"));
//            QIcon fileIcon = iconProvider.icon(fileInfo);
//            button->setIcon(fileIcon);
//        }
//        button->setIconSize(QSize(64, 64));
//        QLabel *label = new QLabel(QFileInfo(filename).fileName());
//        label->setWordWrap(true);
//        label->setMaximumWidth(64);
//        QString folderPath = dirPath + '/' + filename;
//        QString transPath = dirPath + '/' + QFileInfo(filename).filePath();
//        connect(button, &QPushButton::clicked, [=] { MainWindow::onButtonClicked(transPath); });
//        folderName = transPath;
//        //        connect(doubleClickTimer, &QTimer::timeout, = {
//        //            MainWindow::handleDoubleClick(transPath);
//        //        });
//        label->setStyleSheet("color: white");
//        button->setStyleSheet("background-color: transparent");
//        buttonLayout->addWidget(button);
//        buttonLayout->addWidget(label);
//    }
//    ui->foldersFrame->setLayout(buttonLayout);

//    //        ->setLayout(flowLayout);
//    //    ui->tableWidget->verticalHeader()->setVisible(false);
//    //    ui->tableWidget->horizontalHeader()->setVisible(false);
//    //    ui->tableWidget->setStyleSheet("border-radius: 0px");
//    qDebug() << "Current path (render):" << currentPath;
//}

void MainWindow::renderDir(const QString &dirPath)
{
    ui->pathLabel->setText(dirPath);
    currentPath = dirPath;
    QDir directory(dirPath);
    QStringList files = directory.entryList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Files);
    // Создаем сетку
    QGridLayout *gridLayout = new QGridLayout;
    int row = 0;
    int col = 0;

    foreach (const QString &filename, files) {
        QPushButton *button = new QPushButton;
        QFileInfo fileInfo(directory.filePath(filename));
        QFileIconProvider iconProvider;
        if (fileInfo.isDir()) {
            button->setIcon(QIcon(":/new/windowIcon/Resources/Icons/folder.svg"));
        } else {
            button->setIcon(QIcon(":/new/windowIcon/Resources/Icons/file.svg"));
            QIcon fileIcon = iconProvider.icon(fileInfo);
            button->setIcon(fileIcon);
        }
        button->setIconSize(QSize(64, 64));
        QLabel *label = new QLabel(QFileInfo(filename).fileName());
        label->setWordWrap(true);
        label->setMaximumWidth(64);
        QString transPath = dirPath + '/' + QFileInfo(filename).filePath();
        connect(button, &QPushButton::clicked, [=] { MainWindow::onButtonClicked(transPath); });
        folderName = transPath;
        label->setStyleSheet("color: white");
        button->setStyleSheet("QPushButton {background-color: transparent} QPushButton:pressed "
                              "{background-color: #131313; border-radius: 8px}");

        // Добавляем кнопку и лейбл в сетку
        gridLayout->addWidget(button, row, col);
        gridLayout->addWidget(label, row + 1, col);

        // Увеличиваем столбец и переходим на новую строку
        col++;
        if (col > 5) {
            col = 0;
            row += 2;
        }
    }
    ui->folderWidget->setLayout(gridLayout);

    //    setFixedSize(1280, 720);
    //    setCentralWidget(scrollArea);
}

void MainWindow::clearDir()
{
    QLayout *layout = ui->folderWidget->layout();
    if (layout) {
        QLayoutItem *item;
        while ((item = layout->takeAt(0)) != nullptr) {
            delete item->widget(); // Освобождаем виджет
            delete item;           // Освобождаем элемент макета
        }
        delete layout; // Освобождаем сам макет
    }
    //    QTableWidget *table = ui->tableWidget;
    //    table->clear();
    //    int rowCount = table->rowCount();
    //    int columnCount = table->columnCount();

    //    for (int row = 0; row < rowCount; ++row) {
    //        for (int column = 0; column < columnCount; ++column) {
    //            QWidget *widget = table->cellWidget(row, column);
    //            if (widget != nullptr) {
    //                table->removeCellWidget(row, column);
    //                delete widget;
    //            }
    //        }
    //    }
    //    QLayoutItem *item;
    //    while ((item = layout()->takeAt(0)) != nullptr) {
    //        QWidget *widget = item->widget();
    //        if (widget != nullptr) {
    //            delete widget;
    //        }
    //        delete item;
    //    }
}

//folders model

//favourites button hadles

void MainWindow::to_disk()
{
    QStringList drives;
    foreach (const QFileInfo &drive, QDir::drives()) {
        drives << drive.absolutePath();
    }
    clearDir();
    renderDir(drives[1]);
}

void MainWindow::to_fav(QString favPath)
{
    clearDir();
    renderDir(favPath);
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

void MainWindow::createFolder(const QString &folderPath)
{
    QDir dir;
    QInputDialog dialog(this);
    dialog.setOption(QInputDialog::NoButtons);
    bool ok;

    QString inputText
        = dialog.getText(this, "Input name", "Input name of folder:", QLineEdit::Normal, "", &ok);

    if (ok && !inputText.isEmpty()) {
        qDebug() << "Input ok!";
    } else {
        qDebug() << "Input not ok!";
    }

    QString folder = folderPath + "/" + inputText; //путь до папки, которую надо создать

    if (dir.mkdir(folder)) {
        qDebug() << "Folder created! Path:" << folder;
    } else
        qDebug() << "Folder exists";
    clearDir();
    renderDir(currentPath);
}

void MainWindow::on_themeButton_clicked()
{
    static bool isDark = false;
    if (isDark) {
        //        QApplication::setPalette(QApplication::style()->standardPalette());
        ui->frame->setStyleSheet("background-color:#101010");
        isDark = false;
    } else {
        //        QApplication::setStyle(QStyleFactory::create("Fusion"));
        //        QPalette darkPalette;
        //        darkPalette.setColor(QPalette::Window, QColor(22, 22, 22));
        //        darkPalette.setColor(QPalette::WindowText, Qt::white);
        //        darkPalette.setColor(QPalette::Base, QColor(22, 22, 22));
        //        darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
        //        darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
        //        darkPalette.setColor(QPalette::ToolTipText, Qt::white);
        //        darkPalette.setColor(QPalette::Text, Qt::white);
        //        darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
        //        darkPalette.setColor(QPalette::ButtonText, Qt::white);
        //        darkPalette.setColor(QPalette::BrightText, Qt::red);
        //        darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
        //        darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
        //        darkPalette.setColor(QPalette::HighlightedText, Qt::black);
        //        QApplication::setPalette(darkPalette);
        ui->frame->setStyleSheet("background-color:white");
        isDark = true;
    }

    // Перерисовываем все виджеты
    qApp->changeOverrideCursor(QCursor(Qt::WaitCursor));
    qApp->processEvents();
    qApp->setOverrideCursor(QCursor(Qt::ArrowCursor));
}

void MainWindow::propertiesButton(QString folderName)
{
    FileInfoWindow *infoWindow = new FileInfoWindow(folderName, this);
    infoWindow->exec();
}
