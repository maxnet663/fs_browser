#ifndef BROWSER_H
#define BROWSER_H

#include <QObject>
#include <QDir>
#include <QFileSystemModel>

class Browser : public QObject {

    Q_OBJECT
    QDir root_dir;
    bool show_hidden;
    QDir current_dir;
    QFileSystemModel *model;

public:
    Browser(const QDir& root_dir = QDir::homePath(), bool _show_hidden = false);

    ~Browser() override { delete model; }

    QFileSystemModel *getModel() { return model; }

    bool withHidden() const { return show_hidden; }

    QString getDirectoryInfo(const QDir &dir) const;

    QDir getRoot() const { return root_dir; }

signals:
    void dirChanged(const QString &info);

public slots:
    void changeVisibility();

    void setCurrentDir(const QModelIndex &index);

    void unsetCurrentDir(const QModelIndex &index);
};

#endif //BROWSER_H
