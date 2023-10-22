#include "include/list_browser.h"

#include <QDebug>

ListBrowser::ListBrowser(const QDir &root_dir, bool _show_hidden)
: IBrowser(root_dir, _show_hidden) {
    view.setModel(getModel());
    view.setRootIndex(getModel()->index(root_dir.path()));
    connect(&view, &QListView::activated, this, &ListBrowser::changeDir);
    pathCache.push_back(getRoot().path());
}

void ListBrowser::changeDir(const QModelIndex &index) {
    auto path = getModel()->filePath(index);
    qDebug() << "cd to: " + path;
    view.setRootIndex(getModel()->index(path));
    setCurrentDir(path);
    if (!pathCache.contains(path))
        pathCache.push_back(path);
    qDebug() << pathCache;
    emit dirChanged(getDirectoryInfo(path));
}

void ListBrowser::jumpHome()  {
    auto path = getRoot().path();
    qDebug() << "Set to previous dir: " + getCurrentDir().path();
    changeDir(getModel()->index(path));
    setCurrentDir(path);
    pathCache.clear();
    pathCache.push_back(getRoot().path());
    emit dirChanged(getDirectoryInfo(path));
}

void ListBrowser::goBack() {
    if (getCurrentDir() == getRoot() || pathCache.size() <= 1) return;
    auto dest = pathCache.at(pathCache.size() - 2);
    pathCache.pop_back();
    qDebug() << "Go to previous dir: " + dest;
    qDebug() << pathCache;
    changeDir(getModel()->index(dest));
}

void ListBrowser::goForward() { // todo
    if (pathCache.isEmpty()) return;
    auto idx = pathCache.indexOf(getCurrentDir().path());
    if (idx >= pathCache.size() - 1 || idx < 0) return;
    auto dest = pathCache.at(idx + 1);
    qDebug() << "Go to next dir: " + dest;
    qDebug() << pathCache;
    changeDir(getModel()->index(dest));
}