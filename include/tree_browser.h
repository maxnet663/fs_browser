#ifndef TREE_BROWSER_H
#define TREE_BROWSER_H

#include <QObject>
#include <QTreeView>

#include "include/browser.h"

class TreeBrowser : public IBrowser {

    Q_OBJECT
    QTreeView view;

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

    virtual void jumpHome() override;
};

#endif //TREE_BROWSER_H
