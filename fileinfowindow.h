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

        QVBoxLayout *layout = new QVBoxLayout;
        addLabel(layout, "Путь", fileInfo.absoluteFilePath());
        addLabel(layout, "Размер", formatSize(fileInfo.size()));
        addLabel(layout, "Создан", fileInfo.birthTime().toString());
        addLabel(layout, "Послднее изменение", fileInfo.lastModified().toString());
        addLabel(layout, "Тип", fileType(fileInfo));
        addLabel(layout, "", fileInfo.isDir() ? "Папка" : "Файл");

        setLayout(layout);
        setWindowTitle("Информация о файле");
        setFixedSize(400, 200);
    }

    QString formatSize(qint64 sizeInBytes)
    {
        const qint64 kb = 1024;
        const qint64 mb = kb * 1024;
        const qint64 gb = mb * 1024;

        if (sizeInBytes < kb) {
            return QString::number(sizeInBytes) + " Bytes";
        } else if (sizeInBytes < mb) {
            return QString::number(sizeInBytes / kb) + " KB";
        } else if (sizeInBytes < gb) {
            return QString::number(sizeInBytes / mb) + " MB";
        } else {
            return QString::number(sizeInBytes / gb) + " GB";
        }
    }

    QString fileType(const QFileInfo &fileInfo)
    {
        return fileInfo.isDir() ? "Директория" : fileInfo.suffix();
    }

private:
    void addLabel(QVBoxLayout *layout, const QString &labelText, const QString &infoText)
    {
        QLabel *label = new QLabel(labelText + ": " + infoText);
        layout->addWidget(label);
    }
};

#endif // FILEINFOWINDOW_H
