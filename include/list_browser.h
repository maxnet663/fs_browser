#ifndef LISTBROWSER_H
#define LISTBROWSER_H

#include <QListView>
#include <QFileSystemModel>

#include "include/browser.h"

class ListBrowser : public QListView, public Browser {
    Q_OBJECT
public:
    ListBrowser(const QDir &root_dir = QDir::homePath()
                , bool _show_hidden = false);

signals:
    void dirChanged(const QString &info);

    void jumpToHome();

public slots:
    void changeDir(const QModelIndex &index);

};

#endif //LISTBROWSER_H
