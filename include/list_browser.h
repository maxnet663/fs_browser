#ifndef LISTBROWSER_H
#define LISTBROWSER_H

#include <QListView>
#include <QStringList>

#include "include/browser.h"
#include <QSortFilterProxyModel>

class ListBrowser : public IBrowser {

    Q_OBJECT
    QListView view;
    QStringList pathCache;
    QSortFilterProxyModel search_results;

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

    void filterRecords(const QString &text) override;
};

#endif //LISTBROWSER_H
