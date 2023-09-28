#ifndef TABLEMODEL_H
#define TABLEMODEL_H
#include <QDir>
#include <QFileSystemModel>
#include <QTableWidget>
#include <QTableWidgetItem>

class TableModel : public QTableWidget
{
    Q_OBJECT;

public:
    TableModel(QWidget *parent = nullptr) : QTableWidget(parent)
    {
        QFileSystemModel *model = new QFileSystemModel(this);
        model->setRootPath(QDir::rootPath());
        setRowCount(model->rowCount());

        setColumnCount(2); // Два столбца: значок и название

        // Создаем заголовки столбцов (необязательно)
        setHorizontalHeaderLabels({"Значок", "Название"});

        // Заполняем таблицу данными
        for (int row = 0; row < rowCount(); ++row) {
            QModelIndex index = model->index(row, 0);
            QIcon icon = model->fileIcon(index);
            QString name = model->fileName(index);

            QTableWidgetItem *iconItem = new QTableWidgetItem(icon, "");
            QTableWidgetItem *nameItem = new QTableWidgetItem(name);

            setItem(row, 0, iconItem);
            setItem(row, 1, nameItem);
        }

        // Устанавливаем размеры столбцов по содержимому
        resizeColumnsToContents();
    }
};

#endif // TABLEMODEL_H
