#include "mainwindow.h"
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

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    searchWindow = new SearchWindow(this);
    connect(searchWindow, SIGNAL(searchButtonClicked()), this, SLOT(onSearchButtonClicked()));
    //    favoritesWidget = new FavoritesWidget(this);
    searchWindow->hide();
    //    ui->closeButton->setStyleSheet("QPushButton{background: transparent;}");
    //    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setStyleSheet("background-color:#222222");
    ui->scrollArea->verticalScrollBar()->setStyleSheet(
        "QScrollBar:vertical {"
        "    background-color: transparent;"
        "    width: 8px;"
        "    border-radius: 4px;"
        "    border: 0px;"
        "}"
        "QScrollBar::handle:vertical {"
        "    background: #131313;"
        "    border-radius: 4px;"
        "    min-height: 10px;"
        "}"
        "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
        "    background: none;}"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical{ background: none;}");

    //ContextMenu logic
    contextMenu = new QMenu(this);

    QAction *view = contextMenu->addAction("Вид");
    QAction *update = contextMenu->addAction("Обновить");
    QAction *create = contextMenu->addAction("Создать");
    QAction *paste = contextMenu->addAction("Вставить");

    QMenu *sortMenu = contextMenu->addMenu("Сортировка");
    QAction *sortByNameAction = sortMenu->addAction("По имени");
    QAction *sortByTimeAction = sortMenu->addAction("По времени");
    QAction *sortByTypeAction = sortMenu->addAction("По типу");
    QAction *sortBySizeAction = sortMenu->addAction("По размеру");

    connect(sortByNameAction, &QAction::triggered, [=]() {
        currentSort = Name;
        updateDir();
    });
    connect(sortByTimeAction, &QAction::triggered, [=]() {
        currentSort = Date;
        updateDir();
    });
    connect(sortByTypeAction, &QAction::triggered, [=]() {
        currentSort = Type;
        updateDir();
    });
    connect(sortBySizeAction, &QAction::triggered, [=]() {
        currentSort = Size;
        updateDir();
    });
    //    QAction *sort = contextMenu->addAction("Sort");
    //    QAction *properties = contextMenu->addAction("Properties");

    connect(view, &QAction::triggered, this, &MainWindow::actionView);
    //    connect(sort, &QAction::triggered, this, &MainWindow::action2Clicked);
    connect(create, &QAction::triggered, this, &MainWindow::actionCreate);
    connect(update, &QAction::triggered, [=]() { updateDir(); });
    connect(paste, &QAction::triggered, [=]() { actionPaste(); });
    //    connect(properties, &QAction::triggered, [=]() { propertiesButton(folderName); });

    setContextMenuPolicy(Qt::CustomContextMenu);
    contextMenu->setStyleSheet("QMenu:item{background-color: #151515; color: white;} "
                               "QMenu:item:selected {color: #6e6e6e}");

    connect(this, &QWidget::customContextMenuRequested, this, [=](const QPoint &pos) {
        showContextMenu(pos);
    });

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

    connect(ui->Disk1, &QPushButton::clicked, [=]() { to_disk(0); });
    connect(ui->Disk2, &QPushButton::clicked, [=]() { to_disk(1); });

    //    connect(ui->themeButton, &QPushButton::clicked, this, &MainWindow::on_themeButton_clicked);

    //    connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::on_searchButton_clicked);
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
    updateDir(newPath);
}

void MainWindow::on_prevButton_clicked()
{
    updateDir(prevPath);
}

void MainWindow::onButtonClicked(QString folderName)
{
    //    doubleClickTimer->start(QApplication::doubleClickInterval());
    QFileInfo fileInfo(folderName);
    //    QPushButton *senderButton = qobject_cast<QPushButton *>(sender());

    if (fileInfo.isDir()) { //open folder
        currentPath = folderName;
        updateDir(folderName);
    } else if (fileInfo.isFile()) { //open file
        QDesktopServices::openUrl(QUrl::fromLocalFile(folderName));
    }

    qDebug() << folderName;
}

// Слот для обработки двойного щелчка
void MainWindow::handleDoubleClick(QString folderPath)
{
    qDebug() << "Folder path in hanlde: " << folderPath;
    updateDir(folderPath);
}

void MainWindow::sortFiles(QStringList &files, QDir directory)
{
    std::sort(files.begin(),
              files.end(),
              [this, &directory](const QString &file1, const QString &file2) {
                  QFileInfo fileInfo1(directory.filePath(file1));
                  QFileInfo fileInfo2(directory.filePath(file2));

                  switch (currentSort) {
                  case Name:
                      return fileInfo1.fileName() < fileInfo2.fileName();
                  case Size:
                      return fileInfo1.size() < fileInfo2.size();
                  case Date:
                      return fileInfo1.lastModified() < fileInfo2.lastModified();
                  case Type: {
                      if (fileInfo1.isDir() && !fileInfo2.isDir())
                          return true;
                      else if (!fileInfo1.isDir() && fileInfo2.isDir())
                          return false;
                  }
                  default:
                      return false;
                  }
              });
}

void MainWindow::onDirectoryChanged()
{
    QString currDir = QDir::currentPath();
    updateDir(currDir);
}

void MainWindow::renderDir(const QString &dirPath)
{
    ui->pathLabel->setText(dirPath);

    QLabel *label = ui->pathLabel;
    connect(label, &QLabel::linkHovered, [=](const QString &) {
        QLineEdit *lineEdit = new QLineEdit(label->text());

        ui->verticalLayout_4->replaceWidget(label, lineEdit);

        // Удаляем метку из памяти
        label->deleteLater();
    });

    currentPath = dirPath;
    QDir directory(dirPath);
    QStringList files = directory.entryList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Files);
    sortFiles(files, directory);
    try {
        currentFiles.clear();
        for (const QString &file : files) {
            currentFiles.push_back(FileItem(file));
        }
    } catch (Exp error) {
        error.show();
    }
    render(files, directory);
}

void MainWindow::render(QStringList files, QDir directory)
{
    QGridLayout *gridLayout = new QGridLayout;
    int row = 0;
    int col = 0;
    QFileIconProvider iconProvider;
    for (const FileItem &fileItem : currentFiles) {
        QPushButton *button = new QPushButton(this);
        QVBoxLayout *folder = new QVBoxLayout;
        folder->setAlignment(Qt::AlignLeft);

        // Используем значение поля name
        QString fileName = fileItem.getName().toUtf8().constData();

        QFileInfo fileInfo(directory.filePath(fileName));

        if (fileInfo.isDir()) {
            button->setIcon(QIcon(":/new/windowIcon/Resources/Icons/folder.svg"));
        } else {
            QIcon fileIcon = iconProvider.icon(fileInfo);
            if (!fileIcon.isNull()) {
                button->setIcon(QIcon(fileIcon));
            } else {
                button->setIcon(QIcon(":/new/windowIcon/Resources/Icons/file.svg"));
            }
        }

        button->setIconSize(QSize(iconSize, iconSize));
        QLabel *label = new QLabel(fileName);
        label->setWordWrap(true);
        label->setMaximumWidth(iconSize);

        QString transPath = fileInfo.filePath();

        connect(button, &QPushButton::clicked, [=] { MainWindow::onButtonClicked(transPath); });
        folderName = transPath;
        label->setStyleSheet("color: white");
        button->setStyleSheet("QPushButton {background-color: transparent} QPushButton:pressed "
                              "{background-color: #131313; border-radius: 8px}");
        button->setContextMenuPolicy(Qt::CustomContextMenu);

        connect(button, &QPushButton::customContextMenuRequested, [=]() {
            showContextMenu(transPath);
        });

        gridLayout->setAlignment(button, Qt::AlignTop | Qt::AlignHCenter);
        gridLayout->setAlignment(label, Qt::AlignTop | Qt::AlignHCenter);

        gridLayout->addWidget(button, row, col);
        gridLayout->addWidget(label, row + 1, col);

        col++;
        if (col > 5) {
            col = 0;
            row += 2;
        }
    }
    ui->folderWidget->setLayout(gridLayout);
}

void MainWindow::renderSearch(QStringList files)
{
    QVBoxLayout *verticalLayout = new QVBoxLayout;
    foreach (const QString &filename, files) {
        QHBoxLayout *horizontalLayout = new QHBoxLayout;
        QPushButton *button = new QPushButton(this);
        button->setIcon(QIcon(":/new/windowIcon/Resources/Icons/file.svg"));
        button->setIconSize(QSize(iconSize, iconSize));
        QString transPath = QFileInfo(filename).filePath();
        connect(button, &QPushButton::clicked, [=] { MainWindow::onButtonClicked(transPath); });
        QLabel *label = new QLabel(filename);
        label->setStyleSheet("color: white");
        horizontalLayout->addWidget(button);
        horizontalLayout->addWidget(label);
        verticalLayout->addLayout(horizontalLayout);
        horizontalLayout->setAlignment(Qt::AlignLeft);
    }
    verticalLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    ui->folderWidget->setLayout(verticalLayout);
}

void MainWindow::clearSearch()
{
    QWidget *widget;
    while ((widget = ui->folderWidget->findChild<QWidget *>()) != nullptr) {
        delete widget;
    }
}

void MainWindow::clearDir()
{
    QLayout *layout = ui->folderWidget->layout();
    if (layout) {
        QLayoutItem *item;
        while ((item = layout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete layout;
    }
}

//folders model

//favourites button hadles

void MainWindow::to_disk(int x)
{
    QStringList drives;
    foreach (const QFileInfo &drive, QDir::drives()) {
        drives << drive.absolutePath();
    }
    updateDir(drives[x]);
}

void MainWindow::to_fav(QString favPath)
{
    updateDir(favPath);
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
        ui->frame_5->layout()->addWidget(button);
    }
}

void MainWindow::onSearchButtonClicked()
{
    clearDir();
    QStringList foundedFiles = searchWindow->getFilesList();
    if (!foundedFiles.isEmpty()) {
        renderSearch(foundedFiles);
    } else {
    }
}

void MainWindow::on_searchButton_clicked()
{
    clearDir();
    searchWindow->move(this->rect().center().x() - searchWindow->rect().center().x(), 50);
    searchWindow->show();
    searchWindow->setDirectory(currentPath);
    //    QStringList foundedFiles = searchWindow->getFilesList();
    //    renderSearch(foundedFiles);
}

void MainWindow::propertiesButton(QString folderName)
{
    FileInfoWindow *infoWindow = new FileInfoWindow(folderName, this);
    infoWindow->exec();
}

void MainWindow::showContextMenu(const QString &transPath)
{
    QMenu contextMenu(this);
    QAction *deleteAction = new QAction("Удалить", this);
    QAction *properties = new QAction("Свойства", this);
    QAction *copy = contextMenu.addAction("Скопировать");
    QAction *paste = contextMenu.addAction("Вставить");
    QAction *cut = contextMenu.addAction("Вырезать");
    QAction *rename = contextMenu.addAction("Переименовать");

    contextMenu.setStyleSheet("QMenu:item{background-color: #151515; color: white;} "
                              "QMenu:item:selected {color: #6e6e6e}");

    connect(deleteAction, &QAction::triggered, [=]() { actionDelete(transPath); });
    connect(properties, &QAction::triggered, [=]() { propertiesButton(transPath); });
    connect(copy, &QAction::triggered, [=]() { actionCopy(transPath); });
    connect(paste, &QAction::triggered, [=]() { actionPaste(); });
    connect(rename, &QAction::triggered, [=]() { actionRename(transPath); });
    connect(cut, &QAction::triggered, [=]() { actionCut(transPath); });

    contextMenu.addAction(properties);
    contextMenu.addAction(deleteAction);

    QPoint globalPos = QCursor::pos();
    contextMenu.exec(globalPos);
}

void MainWindow::copyDirectory(const QString &sourceDir, const QString &destinationDir)
{
    QDir sourceDirectory(sourceDir);
    QDir destinationDirectory(destinationDir);

    if (!sourceDirectory.exists() || !sourceDirectory.isReadable()) {
        qDebug() << "Невозможно прочитать исходную директорию.";
        return;
    }

    if (!destinationDirectory.exists()) {
        if (!QDir().mkpath(destinationDir)) {
            qDebug() << "Не удалось создать целевую директорию.";
            return;
        }
    }

    // Получаем список файлов и поддиректорий внутри исходной директории
    QStringList fileList = sourceDirectory.entryList(QDir::Files | QDir::Dirs
                                                     | QDir::NoDotAndDotDot);

    foreach (const QString &fileName, fileList) {
        QString sourcePath = sourceDir + QDir::separator() + fileName;
        QString destinationPath = destinationDir + QDir::separator() + fileName;

        if (QFileInfo(sourcePath).isDir()) {
            // Если это поддиректория, рекурсивно копируем её содержимое
            copyDirectory(sourcePath, destinationPath);
        } else {
            // Если это файл, просто копируем его
            if (QFile::copy(sourcePath, destinationPath)) {
                qDebug() << "Файл успешно скопирован: " << destinationPath;
            } else {
                qDebug() << "Не удалось скопировать файл: " << destinationPath;
            }
        }
    }
}

void MainWindow::actionCopy(const QString &source)
{
    QMimeData *mimeData = new QMimeData;
    QList<QUrl> urls;
    urls.append(QUrl::fromLocalFile(source));
    mimeData->setUrls(urls);

    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setMimeData(mimeData);
    qDebug() << "File copied";
}

void MainWindow::copyToDestination(const QString &sourcePath)
{
    QFileInfo sourceFileInfo(sourcePath);
    if (sourceFileInfo.isFile()) {
        QString fileName = sourceFileInfo.fileName();
        QString destinationPathWithFileName = currentPath + QDir::separator() + fileName;

        if (QFile::copy(sourcePath, destinationPathWithFileName)) {
            qDebug() << "Файл успешно скопирован: " << destinationPathWithFileName;
        } else {
            qDebug() << "Не удалось скопировать файл: " << destinationPathWithFileName;
        }
    } else if (sourceFileInfo.isDir()) {
        QDir sourceDir(sourcePath);
        QString destinationDirPath = currentPath + QDir::separator() + sourceDir.dirName();

        // Вызываем функцию для рекурсивного копирования содержимого директории
        copyDirectory(sourcePath, destinationDirPath);
        qDebug() << "Директория успешно скопирована: " << destinationDirPath;
    }
}

void MainWindow::actionPaste()
{
    QClipboard *clipboard = QGuiApplication::clipboard();
    const QMimeData *mimeData = clipboard->mimeData();

    if (mimeData->hasUrls()) {
        QList<QUrl> urlList = mimeData->urls();
        foreach (QUrl url, urlList) {
            QString sourcePath = url.toLocalFile();
            qDebug() << "вставка";

            if (cutProgress) {
                copyToDestination(sourcePath);
                actionDelete(sourcePath);
                updateDir();
            } else {
                copyToDestination(sourcePath);
                updateDir();
            }
        }
        cutProgress = false;
    }
}

bool MainWindow::messageDisplay()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,
                                  "Подтверждение удаления",
                                  "Вы уверены, что хотите удалить?",
                                  QMessageBox::Yes | QMessageBox::No);
    return (reply == QMessageBox::Yes);
}

void MainWindow::actionView()
{
    switch (currentIconSize) {
    case Big: {
        iconSize = 256;
        currentIconSize = Medium;
        break;
    }
    case Medium: {
        iconSize = 128;
        currentIconSize = Small;
        break;
    }
    case Small: {
        iconSize = 64;
        currentIconSize = Big;
        break;
    }
    }
    updateDir();
}

void MainWindow::actionDelete(const QString &path)
{
    QFileInfo fileInfo(path);
    if (fileInfo.isFile()) {
        if (!cutProgress) {
            if (messageDisplay()) {
                QFile file(path);
                file.remove();
                QMessageBox::information(this, "Успех", "Файл успешно удален.");
            }
        } else {
            QFile file(path);
            file.remove();
        }
    } else if (fileInfo.isDir()) {
        if (!cutProgress) {
            if (messageDisplay()) {
                QDir dir(path);
                if (dir.removeRecursively()) {
                    QMessageBox::information(this, "Успех", "Директория успешно удалена.");
                } else {
                    QMessageBox::warning(this, "Ошибка", "Не удалось удалить директорию.");
                }
            }
        } else {
            QDir dir(path);
            dir.removeRecursively();
        }
    }
    updateDir();
}

void MainWindow::actionRename(const QString &oldPath)
{
    QFileInfo fileInfo(oldPath);
    QString oldName = fileInfo.fileName();

    QString newName = inputNameDialog();

    if (newName.isEmpty()) {
        qDebug() << "Renaming canceled or no new name entered.";
        return;
    }

    QString newPath = QDir(fileInfo.absolutePath()).filePath(newName);

    if (QFile::rename(oldPath, newPath)) {
        qDebug() << "Successfully renamed to" << newPath;
    } else {
        qDebug() << "Failed to rename.";
    }
    updateDir();
}

void MainWindow::actionCut(const QString &source)
{
    cutProgress = true;
    actionCopy(source);
}

void MainWindow::createFolder(const QString &folderPath)
{
    QDir dir;
    QString inputText = inputNameDialog();

    if (inputText.isEmpty()) {
        qDebug() << "Folder creation canceled or no name entered.";
        return;
    }

    QString folder = folderPath + QDir::separator() + inputText;

    if (dir.mkdir(folder)) {
        qDebug() << "Folder created! Path:" << folder;
    } else {
        qDebug() << "Folder exists";
    }

    updateDir();
}

QString MainWindow::inputNameDialog()
{
    QInputDialog dialog(this);
    dialog.setWindowFlags(dialog.windowFlags() & ~Qt::WindowContextHelpButtonHint);
    dialog.setWindowTitle("Ввод имени");
    dialog.setLabelText("Введите название:");
    //    dialog.setTextEchoMode(QLineEdit::Password);

    dialog.setStyleSheet("color: white;");
    dialog.setInputMode(QInputDialog::TextInput);

    QLineEdit *lineEdit = dialog.findChild<QLineEdit *>();
    if (lineEdit) {
        lineEdit->setStyleSheet("border: 2px solid #151515; border-radius: 24px;");
        QRegExpValidator *validator = new QRegExpValidator(QRegExp("[^\\\\/:*?\"<>|]*"), this);
        lineEdit->setValidator(validator);
    }

    if (dialog.exec() == QDialog::Accepted && !dialog.textValue().isEmpty()) {
        return dialog.textValue();
    } else
        return QString();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape && searchWindow->isVisible()) {
        clearSearch();
        searchWindow->hide();
        searchWindow->clearFounded();
        clearDir();
        renderDir(currentPath);
    }
};

void MainWindow::updateDir(const QString &path)
{
    clearDir();
    renderDir(path);
}

void MainWindow::updateDir()
{
    clearDir();
    renderDir(currentPath);
}

void MainWindow::on_themeButton_clicked()
{
    static bool isDark = false;
    if (isDark) {
        ui->frame->setStyleSheet("background-color:#151515");
        isDark = false;
    } else {
        ui->frame->setStyleSheet("background-color:white; color: black");
        isDark = true;
    }

    // Перерисовываем все виджеты
    qApp->changeOverrideCursor(QCursor(Qt::WaitCursor));
    qApp->processEvents();
    qApp->setOverrideCursor(QCursor(Qt::ArrowCursor));
}
