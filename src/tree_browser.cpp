#include "include/tree_browser.h"

#include <QDebug>

TreeBrowser::TreeBrowser(const QDir &root_dir, bool _show_hidden)
: Browser(root_dir, _show_hidden) {
    QObject::connect(this, &QTreeView::expanded
                     , this, &Browser::setCurrentDir);
    QObject::connect(this, &QTreeView::collapsed
                     , this, &Browser::unsetCurrentDir);
//    QObject::connect(this,)
}

void TreeBrowser::printParentInfo(const QModelIndex &index) {
    auto dir_path = getModel()->fileInfo(index).absolutePath()
                    + "/"
                    + index.data().toString();
    auto dir = QDir(dir_path);
    qDebug() << "Print info about: " + dir_path;
    emit dirChanged(getDirectoryInfo(dir));
//    printDirectoryInfo(dir);
}

void TreeBrowser::printChildInfo(const QModelIndex &index) {
    auto dir_path = getModel()->fileInfo(index).absolutePath();
    auto dir = QDir(dir_path);
    qDebug() << "Printing info about parent: " + dir_path;
//    emit dir
//    printDirectoryInfo(dir);
}
