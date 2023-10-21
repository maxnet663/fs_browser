#include "include/list_browser.h"

#include <QDebug>

ListBrowser::ListBrowser(const QDir &root_dir, bool _show_hidden)
: IBrowser(root_dir, _show_hidden) {
    view.setModel(getModel());
    view.setRootIndex(getModel()->index(root_dir.path()));
    connect(&view, &QListView::activated, this, &ListBrowser::changeDir);
}

void ListBrowser::changeDir(const QModelIndex &index) {
    auto path = getModel()->filePath(index);
    qDebug() << "cd to: " + path;
    view.setRootIndex(getModel()->index(path));
    IBrowser::setCurrentDir(path);
    emit dirChanged(getDirectoryInfo(path));
}

void ListBrowser::jumpHome()  {
    auto home = getModel()->index(getRoot().path());
    changeDir(home);
    IBrowser::setCurrentDir(getRoot().path());
    emit dirChanged(getDirectoryInfo(getRoot().path()));
}
