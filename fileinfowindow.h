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
        addLabel(layout, "Path", fileInfo.absoluteFilePath());
        addLabel(layout, "Size", formatSize(fileInfo.size()));
        addLabel(layout, "Created", fileInfo.birthTime().toString());
        addLabel(layout, "Last Modified", fileInfo.lastModified().toString());
        addLabel(layout, "Type", fileType(fileInfo));
        addLabel(layout, "Is Directory", fileInfo.isDir() ? "Yes" : "No");

        setLayout(layout);
        setWindowTitle("File Information");
        setFixedSize(300, 200);
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
        return fileInfo.isDir() ? "Directory" : fileInfo.suffix();
    }

private:
    void addLabel(QVBoxLayout *layout, const QString &labelText, const QString &infoText)
    {
        QLabel *label = new QLabel(labelText + ": " + infoText);
        layout->addWidget(label);
    }
};

#endif // FILEINFOWINDOW_H
