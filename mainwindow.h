#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "favoriteswidget.h"
#include "searchwindow.h"
//#include "tablemodel.h"
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
    enum SortCriterion { Name, Size, Date, Type };

public slots:
    QString inputNameDialog();
    void createFolder(const QString &folderPath);
    void onButtonClicked(QString folderName);
    void onSearchButtonClicked();

private slots:

    void showContextMenu(const QString &folder);
    void showContextMenu(const QPoint &pos) { contextMenu->exec(mapToGlobal(pos)); }
    void updateDir(const QString &path);
    void updateDir();
    void action1Clicked() { qDebug() << "Doing 1 clicked"; }
    void actionCreate() { createFolder(currentPath); }
    void actionDelete(const QString &path);
    void actionCopy(const QString &source);
    void copyDirectory(const QString &sourceDir, const QString &destinationDir);
    void copyToDestination(const QString &source);
    void actionPaste();
    void actionRename(const QString &oldpath);
    void actionCut(const QString &path);

    void on_closeButton_clicked();
    void on_maximizeButton_clicked();
    void on_minimizeButton_clicked();
    void on_backButton_clicked();
    void on_prevButton_clicked();
    void on_themeButton_clicked();
    void on_searchButton_clicked();
    void handleDoubleClick(QString folderName);
    void onDirectoryChanged();
    //render
    void renderDir(const QString &dirPath);
    void render(QStringList files, QDir directory);
    void renderSearch(QStringList files);
    void clearDir();
    void clearSearch();

    void to_disk(int x);
    void to_fav(QString favPath);
    void getDriveList();
    void propertiesButton(QString folderName);

    //    void updateGrid();
    void keyPressEvent(QKeyEvent *event);

    void sortFiles(QStringList &files, QDir directory);
    bool messageDisplay();

private:
    Ui::MainWindow *ui;
    QMenu *contextMenu;
    SortCriterion currentSort;
    QString currentPath;
    QString folderName;
    QString prevPath;
    SearchWindow *searchWindow;
    bool cutProgress = false;
};

#endif // MAINWINDOW_H
