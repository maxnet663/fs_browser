#ifndef TREE_BROWSER_H
#define TREE_BROWSER_H

#include <QObject>
#include <QTreeView>
#include <QSortFilterProxyModel>

#include "include/browser.h"

class TreeBrowser : public IBrowser {

    Q_OBJECT
    QTreeView view;
    QSortFilterProxyModel *search_results;

public:
    TreeBrowser(const QDir &root_dir = QDir::homePath()
            , bool _show_hidden = false);

    QTreeView *getView() { return &view; }

    ~TreeBrowser() override = default;
//signals:
//    void dirChanged(const QString &info);

public slots:
    void switchParent(const QModelIndex &index);

    void switchChild(const QModelIndex &index);

    void jumpHome() override;

    void filterRecords(const QString &text) override;
};

#endif //TREE_BROWSER_H
