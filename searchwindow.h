#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include <QWidget>

namespace Ui {
class SearchWindow;
}

class SearchWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SearchWindow(QWidget *parent = nullptr);
    ~SearchWindow();

public slots:
    void onTextChanged(const QString &text);
    void setDirectory(const QString &dir);
    QStringList getFilesList();
    void searchFiles(const QString &directoryPath, const QString &targetFileName);
    void clearFounded();

private:
    Ui::SearchWindow *ui;
    QString currentDir;
    QStringList foundFiles;
};

#endif // SEARCHWINDOW_H
