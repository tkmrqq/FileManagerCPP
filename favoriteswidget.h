#ifndef FAVORITESWIDGET_H
#define FAVORITESWIDGET_H

#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class FavoritesWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FavoritesWidget(QWidget *parent = nullptr);

    void addFavorite(const QString &path);
    QLayout *getLayout() const;

signals:
    void directoryClicked(const QString &path);

private slots:
    void onStandardDirectoryClicked(const QString &path);
    void onFavoriteClicked(const QString &path);
    void onAddFavoriteClicked();

private:
    QVBoxLayout *layout_;
    QStringList favorites_;

    void setupUi();
    void addStandardDirectoryButton(const QString &path, const QString &text);
    void addFavoriteButton(const QString &path);
    void updateButtons();
    void loadFavorites();
    void saveFavorites();
};

#endif // FAVORITESWIDGET_H
