#ifndef TREE_BROWSER_H
#define TREE_BROWSER_H

#include <QObject>
#include <QTreeView>
#include <QSortFilterProxyModel>

#include "include/browser.h"

class TreeBrowser : public IBrowser {

    Q_OBJECT
    QTreeView view;

public:
    TreeBrowser(const QDir &root_dir = QDir::homePath()
            , bool _show_hidden = false);

    ~TreeBrowser() override = default;

    /**
     * View getter
     * @return pointer to view
     */
    QTreeView *getView() { return &view; }

public slots:
    /**
     * when record collapsed, sets to current dir its parent
     * @param index collapsed record
     */
    void switchParent(const QModelIndex &index);

    /**
     * when record expanded, sets it to current dir
     * @param index
     */
    void switchChild(const QModelIndex &index);

    /**
     * collapse all expanded records
     */
    void jumpHome() override;
};

#endif //TREE_BROWSER_H
