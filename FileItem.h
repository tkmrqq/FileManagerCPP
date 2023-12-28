#ifndef FILEITEM_H
#define FILEITEM_H

#include "myString.h"
#include "myVector.h"
#include <QtCore>

class FileItem
{
    MyString name;
    qint64 size;
    QDateTime createdDate;

public:
    FileItem(const QString &name, qint64 size, const QDateTime &created);
    MyString getName() const { return name; }
    qint64 getSize() const { return size; }
    QDateTime getCreatedDate() const { return createdDate; }
};

#endif // FILEITEM_H
