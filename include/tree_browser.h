#ifndef TREE_BROWSER_H
#define TREE_BROWSER_H

#include <QTreeView>

#include "include/browser.h"

class TreeBrowser : public QTreeView, public Browser {
public:
    TreeBrowser(const QDir &root_dir = QDir::homePath()
            , bool _show_hidden = false);

signals:
//    void dirChanged(const QString &info);

public slots:
    void printParentInfo(const QModelIndex &index);

    void printChildInfo(const QModelIndex &index);
};

#endif //TREE_BROWSER_H
