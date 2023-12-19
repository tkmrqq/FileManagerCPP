#ifndef FILEINFOLIST_H
#define FILEINFOLIST_H

#include <QAbstractTableModel>
#include <QFileInfo>
#include <QtWidgets>

class FileInfoList : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit FileInfoList(QObject *parent = nullptr);
    ~FileInfoList();

    qint64 getSize() const;
    QDateTime getLastModified() const;
    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent) const override;
    void setQFileInfoList(const QList<QFileInfo> &fileInfos);

private:
    QList<QFileInfo> fileList;
    QStringList header;
};

#endif // FILEINFOLIST_H
