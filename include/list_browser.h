#ifndef LISTBROWSER_H
#define LISTBROWSER_H

#include <QListView>
#include <QStringList>

#include "include/browser.h"

class ListBrowser : public IBrowser {

    Q_OBJECT
    QListView view;
    QStringList pathCache;

public:
    ListBrowser(const QDir &root_dir = QDir::homePath()
                , bool _show_hidden = false);

    QListView *getView() { return &view; }

    ~ListBrowser() override = default;

public slots:
    void changeDir(const QModelIndex &index);

    void jumpHome() override;

    void goBack();

    void goForward(); // todo
};

#endif //LISTBROWSER_H
