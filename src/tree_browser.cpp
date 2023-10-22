#include "include/tree_browser.h"

#include <QDebug>
#include <QStandardItemModel>

TreeBrowser::TreeBrowser(const QDir &root_dir, bool _show_hidden)
: IBrowser(root_dir, _show_hidden) {
    view.setModel(getModel());
    view.setRootIndex(getModel()->index(root_dir.path()));
    view.setSortingEnabled(true);
    view.setColumnWidth(0, 250);
    view.sortByColumn(0, Qt::SortOrder::AscendingOrder);

    connect(&view, &QTreeView::expanded
                     , this, &TreeBrowser::switchChild);
    connect(&view, &QTreeView::collapsed
                     , this, &TreeBrowser::switchParent);
}

void TreeBrowser::switchChild(const QModelIndex &index) {
    auto dir_path = getModel()->fileInfo(index).absolutePath()
                    + "/"
                    + index.data().toString();
    auto dir = QDir(dir_path);
    IBrowser::setCurrentDir(dir);
    emit dirChanged(getDirectoryInfo(dir));
    qDebug() << "Print info about child: " + dir_path;
}

void TreeBrowser::switchParent(const QModelIndex &index) {
    auto dir_path = getModel()->fileInfo(index).absolutePath();
    auto dir = QDir(dir_path);
    IBrowser::setCurrentDir(dir);
    emit dirChanged(getDirectoryInfo(dir));
    qDebug() << "Print info about parent: " + dir_path;
}

void TreeBrowser::jumpHome() {
    view.collapseAll();
    IBrowser::setCurrentDir(IBrowser::getRoot());
    emit dirChanged(getDirectoryInfo(getRoot()));
}

void TreeBrowser::filterRecords(const QString &text) {
    auto model = getModel();
    if (text.isEmpty()) {
        model->setNameFilterDisables(true);
        model->setNameFilters(QStringList());
        return;
    }
    model->setNameFilterDisables(true);
    model->setNameFilters(QStringList(text));
}
