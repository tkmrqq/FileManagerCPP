#include "favoriteswidget.h"
#include <QDir>
#include <QFileDialog>
#include <QSettings>
#include <QStandardPaths>

FavoritesWidget::FavoritesWidget(QWidget *parent) : QWidget(parent)
{
    setupUi();
    loadFavorites();
}

void FavoritesWidget::addFavorite(const QString &path)
{
    favorites_.append(path);
    updateButtons();
    saveFavorites();
}

QLayout *FavoritesWidget::getLayout() const
{
    return layout_;
}

void FavoritesWidget::onStandardDirectoryClicked(const QString &path)
{
    emit directoryClicked(path);
}

void FavoritesWidget::onFavoriteClicked(const QString &path)
{
    emit directoryClicked(path);
}

void FavoritesWidget::onAddFavoriteClicked()
{
    QString directory = QFileDialog::getExistingDirectory(this, tr("Выберите директорию"));
    if (!directory.isEmpty()) {
        addFavorite(directory);
    }
}

void FavoritesWidget::setupUi()
{
    layout_ = new QVBoxLayout(this);

    addStandardDirectoryButton(QDir::homePath(), tr("Домашняя директория"));
    addStandardDirectoryButton(QDir::rootPath(), tr("Корневая директория"));
    addStandardDirectoryButton(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),
                               tr("Рабочий стол"));
    updateButtons();

    QPushButton *addFavoriteButton = new QPushButton(tr("Добавить фаворит"));
    connect(addFavoriteButton, &QPushButton::clicked, this, &FavoritesWidget::onAddFavoriteClicked);
    layout_->addWidget(addFavoriteButton);
}

void FavoritesWidget::addStandardDirectoryButton(const QString &path, const QString &text)
{
    QPushButton *button = new QPushButton(text);
    connect(button, &QPushButton::clicked, this, [this, path]() {
        onStandardDirectoryClicked(path);
    });
    layout_->addWidget(button);
}

void FavoritesWidget::addFavoriteButton(const QString &path)
{
    QPushButton *button = new QPushButton(path);
    connect(button, &QPushButton::clicked, this, [this, path]() { onFavoriteClicked(path); });
    layout_->addWidget(button);
}

void FavoritesWidget::updateButtons()
{
    QLayoutItem *child;
    while ((child = layout_->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    for (const QString &path : favorites_) {
        addFavoriteButton(path);
    }
}

void FavoritesWidget::loadFavorites()
{
    QSettings settings;
    favorites_ = settings.value("favorites").toStringList();
}

void FavoritesWidget::saveFavorites()
{
    QSettings settings;
    settings.setValue("favorites", favorites_);
}
