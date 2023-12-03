#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "flowlayout.h"
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
    void style();

public slots:
    void createFolder(const QString &folderPath);

private slots:

    void action1Clicked() { qDebug() << "Doing 1 clicked"; }
    void action2Clicked() { qDebug() << "Doing 2 clicked"; }
    void actionCreate() { createFolder(currentPath); }

    void showContextMenu(const QPoint &pos) { contextMenu->exec(mapToGlobal(pos)); }

    void on_closeButton_clicked();
    void on_maximizeButton_clicked();
    void on_minimizeButton_clicked();
    void on_backButton_clicked();
    void on_prevButton_clicked();
    void on_themeButton_clicked();
    void onButtonClicked(QString folderName);
    void handleDoubleClick(QString folderName);
    void onDirectoryChanged();
    void renderDir(const QString &dirPath);
    void clearDir();
    void to_disk();
    void to_fav(QString favPath);
    void getDriveList();
    void propertiesButton(QString folderName);
    //    void updateGrid();

private:
    Ui::MainWindow *ui;
    QFileSystemModel *dirmodel;
    QMenu *contextMenu;
    QTimer *doubleClickTimer;
    QFileSystemWatcher *fileSystemWatcher;
    QString currentPath;
    QString folderName;
    QString prevPath;
    FlowLayout *flowLayout;
};



#endif // MAINWINDOW_H
