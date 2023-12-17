#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "searchwindow.h"
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
    QString inputNameDialog();
    void createFolder(const QString &folderPath);
    void onButtonClicked(QString folderName);

private slots:

    void showContextMenu(const QString &folder);
    void showContextMenu(const QPoint &pos) { contextMenu->exec(mapToGlobal(pos)); }
    void updateDir(const QString &path);
    void action1Clicked() { qDebug() << "Doing 1 clicked"; }
    void action2Clicked() { qDebug() << "Doing 2 clicked"; }

    void actionCreate() { createFolder(currentPath); }
    void actionDelete(const QString &path);
    void actionCopy(const QString &source);
    void copyToDestination(const QString &source);
    void actionPaste();
    void actionRename(const QString &oldpath);

    void on_closeButton_clicked();
    void on_maximizeButton_clicked();
    void on_minimizeButton_clicked();
    void on_backButton_clicked();
    void on_prevButton_clicked();
    void on_themeButton_clicked();
    void on_searchButton_clicked();
    //    void onButtonClicked(QString folderName); //moved to public slots (undo if needed)
    void handleDoubleClick(QString folderName);
    void onDirectoryChanged();
    //render
    void renderDir(const QString &dirPath);
    void render(QStringList files, QDir directory);
    void renderSearch(QStringList files);
    void clearDir();

    void to_disk(int x);
    void to_fav(QString favPath);
    void getDriveList();
    void propertiesButton(QString folderName);

    //    void updateGrid();
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;
    QFileSystemModel *dirmodel;
    QMenu *contextMenu;
    QTimer *doubleClickTimer;
    QFileSystemWatcher *fileSystemWatcher;
    QString currentPath;
    QString folderName;
    QString prevPath;
    SearchWindow *searchWindow;
};

#endif // MAINWINDOW_H
