#include "include/list_browser.h"

#include <QDebug>

ListBrowser::ListBrowser(const QDir &root_dir, bool _show_hidden)
: Browser(root_dir, _show_hidden) {
    QObject::connect(this, &QListView::activated
                     , this, &Browser::setCurrentDir);
}

void ListBrowser::changeDir(const QModelIndex &index) {
    auto path = getModel()->filePath(index);
    qDebug() << "cd to: " + path;
    setRootIndex(getModel()->index(path));
    setCurrentDir(index);
//    emit dirChanged(getDirectoryInfo(path));
}

void ListBrowser::jumpToHome() {
    auto home = getModel()->index(getRoot().path());
    changeDir(home);
    setCurrentDir(home);
//    emit dirChanged(getDirectoryInfo(getRoot().path()));
}
