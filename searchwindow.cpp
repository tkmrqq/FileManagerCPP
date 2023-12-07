#include "searchwindow.h"
#include "ui_searchwindow.h"
#include <QDebug>
#include <QDir>

SearchWindow::SearchWindow(QWidget *parent) : QWidget(parent), ui(new Ui::SearchWindow)
{
    ui->setupUi(this);

    connect(ui->lineEdit,
            SIGNAL(textChanged(const QString &)),
            this,
            SLOT(onTextChanged(const QString &)));
}

SearchWindow::~SearchWindow()
{
    delete ui;
}

void SearchWindow::onTextChanged(const QString &text)
{
    searchFiles(currentDir, text);
}

void SearchWindow::setDirectory(const QString &dir)
{
    this->currentDir = dir;
}

void SearchWindow::searchFiles(const QString &directoryPath, const QString &targetFileName)
{
    QDir directory(directoryPath);

    if (!directory.exists()) {
        qDebug() << "Указанный каталог не существует.";
        return;
    }

    QStringList filters;
    filters << targetFileName;

    directory.setNameFilters(filters);
    directory.setFilter(QDir::Files | QDir::NoSymLinks | QDir::Dirs);

    QFileInfoList fileList = directory.entryInfoList();

    if (fileList.isEmpty()) {
        qDebug() << "Файлы с именем" << targetFileName << "не найдены в каталоге" << directoryPath;
    } else {
        qDebug() << "Найденные файлы с именем" << targetFileName << "в каталоге" << directoryPath
                 << ":";

        for (const QFileInfo &fileInfo : fileList) {
            foundFiles << fileInfo.filePath();
            qDebug() << fileInfo.filePath();
        }
    }
}

QStringList SearchWindow::getFilesList()
{
    return this->foundFiles;
}
