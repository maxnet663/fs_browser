#ifndef BROWSER_H
#define BROWSER_H

#include <QObject>
#include <QDir>
#include <QFileSystemModel>

class IBrowser : public QObject{

    Q_OBJECT
    QDir root_dir;
    bool show_hidden;
    QDir current_dir;
    QFileSystemModel model;

public:
    IBrowser(const QDir& root_dir = QDir::homePath(), bool _show_hidden = false);

    QFileSystemModel *getModel() { return &model; }

    bool withHidden() const { return show_hidden; }

    QString getDirectoryInfo(const QDir &dir) const;

    QDir getRoot() const { return root_dir; }

    QDir getCurrentDir() const { return current_dir; }

    virtual ~IBrowser() = default;

signals:
    void dirChanged(const QString &info);

public slots:

    void turnVisibility();

    void setCurrentDir(const QDir &dir);

    virtual void jumpHome() = 0;
};

#endif //BROWSER_H
