#include "fileinfolist.h"

FileInfoList::FileInfoList(QObject *parent) : QAbstractTableModel(parent)
{
    //make a header
    header << "Name"
           << "Type"
           << "Path";
}

FileInfoList::~FileInfoList() {}

int FileInfoList::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return header.size();
}

int FileInfoList::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return fileList.size();
}
