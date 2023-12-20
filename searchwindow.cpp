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

void SearchWindow::searchFiles(const QString &directoryPath, const QString &targetSubstring)
{
    foundFiles.clear(); // Очищаем найденные файлы перед новым поиском

    if (directoryPath.isEmpty() || targetSubstring.isEmpty()) {
        qDebug() << "Указаны неверные параметры для поиска.";
        return;
    }

    QDir directory(directoryPath);

    if (!directory.exists()) {
        qDebug() << "Указанный каталог не существует.";
        return;
    }

    QStringList filters;
    filters << "*"; // Устанавливаем фильтр для всех файлов и папок

    directory.setNameFilters(filters);
    directory.setFilter(QDir::Files | QDir::NoSymLinks | QDir::Dirs | QDir::NoDotAndDotDot);

    QFileInfoList fileList = directory.entryInfoList();

    if (fileList.isEmpty()) {
        qDebug() << "Файлы и папки с подстрокой" << targetSubstring << "не найдены в каталоге"
                 << directoryPath;
    } else {
        qDebug() << "Найденные файлы и папки с подстрокой" << targetSubstring << "в каталоге"
                 << directoryPath << ":";

        for (const QFileInfo &fileInfo : fileList) {
            // Проверяем, содержится ли подстрока в имени файла или папки
            if (fileInfo.fileName().contains(targetSubstring, Qt::CaseInsensitive)) {
                foundFiles << fileInfo.filePath();
                qDebug() << fileInfo.filePath();
            }
        }
    }
}

void SearchWindow::clearFounded()
{
    foundFiles.clear();
}

QStringList SearchWindow::getFilesList()
{
    return this->foundFiles;
}
