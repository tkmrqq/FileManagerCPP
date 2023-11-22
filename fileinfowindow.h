#ifndef FILEINFOWINDOW_H
#define FILEINFOWINDOW_H

#include <QDateTime>
#include <QDialog>
#include <QFileInfo>
#include <QLabel>
#include <QVBoxLayout>

class FileInfoWindow : public QDialog
{
    Q_OBJECT

public:
    FileInfoWindow(const QString &filePath, QWidget *parent = nullptr) : QDialog(parent)
    {
        QFileInfo fileInfo(filePath);

        QLabel *pathLabel = new QLabel("Path: " + fileInfo.absoluteFilePath());
        QLabel *sizeLabel = new QLabel("Size: " + QString::number(fileInfo.size() / 8 / 1024)
                                       + " Mb");
        QLabel *createdLabel = new QLabel("Created: " + fileInfo.birthTime().toString());
        // Добавьте другие свойства, которые вы хотите отобразить

        QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(pathLabel);
        layout->addWidget(sizeLabel);
        layout->addWidget(createdLabel);
        // Добавьте другие виджеты для отображения свойств
        setLayout(layout);
        setWindowTitle("File Information");
    }
};

#endif // FILEINFOWINDOW_H
