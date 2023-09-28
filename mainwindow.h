#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "tablemodel.h"
#include <QMainWindow>
#include <QtWidgets>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    ~MainWindow();
    MainWindow(QWidget* parent = nullptr);
    //widget
    TableModel *tableModel = new TableModel(this);

private slots:

    void action1Clicked() { qDebug() << "Doing 1 clicked"; }

    void action2Clicked(){
        qDebug() << "Doing 2 clicked";
    }

    void showContextMenu(const QPoint &pos){
        contextMenu->exec(mapToGlobal(pos));
    }

    void on_closeButton_clicked();
    void on_maximizeButton_clicked();
    void on_minimizeButton_clicked();
    void on_backButton_clicked();
    void onButtonClicked(QString folderName);
    void handleDoubleClick(QString folderName);
    void onDirectoryChanged();
    void renderDir(const QString &dirPath);
    void clearDir();
    void to_desktop();
    void to_disk();
    void getDriveList();
    //    void updateGrid();

private:
    Ui::MainWindow *ui;
    QFileSystemModel *dirmodel;
    QMenu *contextMenu;
    QTimer *doubleClickTimer;
    QFileSystemWatcher *fileSystemWatcher;
    QString currentPath;
};



#endif // MAINWINDOW_H
