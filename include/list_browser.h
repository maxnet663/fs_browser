#ifndef LISTBROWSER_H
#define LISTBROWSER_H

#include <QListView>

#include "include/browser.h"

class ListBrowser : public IBrowser {

    Q_OBJECT
    QListView view;

public:
    ListBrowser(const QDir &root_dir = QDir::homePath()
                , bool _show_hidden = false);

    QListView *getView() { return &view; }

    ~ListBrowser() override = default;

//signals:
//    void dirChanged(const QString &info);

public slots:
    void changeDir(const QModelIndex &index);

    void jumpHome() override;
};

#endif //LISTBROWSER_H
