#ifndef FILEITEM_H
#define FILEITEM_H

#include "myString.h"
#include "myVector.h"
#include <QtCore>

class FileItem
{
    QString name;
    qint64 size;
    QDateTime createdDate;

public:
    FileItem(){};
    FileItem(const QString &name, qint64 size, const QDateTime &created);
    FileItem(const QString &qstr) { name = qstr; };
    QString getName() const { return name; }
    qint64 getSize() const { return size; }
    QDateTime getCreatedDate() const { return createdDate; }
};

#endif // FILEITEM_H
