#include "include/browser.h"

#include <QDebug>

IBrowser::IBrowser(const QDir& root_dir, bool _show_hidden)
: root_dir(root_dir), show_hidden(_show_hidden) {
    model.setRootPath(root_dir.path());
    model.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    current_dir = root_dir;
}

QString IBrowser::getDirectoryInfo(const QDir &dir) const {
    int files_num, dir_num;
    if (show_hidden) {
        files_num = dir.entryList(QDir::Hidden | QDir::Files).count();
        dir_num = dir.entryList(QDir::Hidden
                                     | QDir::Dirs
                                     | QDir::NoDotAndDotDot).count();
    } else {
        files_num = dir.entryList(QDir::Files).count();
        dir_num = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot).count();
    }
    auto msg = dir.path() +
            QString(" \t Files: %1, Directories: %2").arg(files_num).arg(dir_num);
    return msg;
}

void IBrowser::turnVisibility() {
    show_hidden = !show_hidden;
    if (show_hidden) {
        model.setFilter(QDir::AllEntries
                        | QDir::NoDotAndDotDot
                        | QDir::Hidden);
    } else {
        model.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    }
    qDebug() << "Current dir:" << current_dir;
    if (!current_dir.isEmpty())
        getDirectoryInfo(current_dir);
    else
        getDirectoryInfo(root_dir);
}

void IBrowser::setCurrentDir(const QDir &dir) {
    qDebug() << "Set to current dir: " + dir.path();
    current_dir = dir;
}

//void Browser::setCurrentDir(const QModelIndex &index) {
//    auto path = model->fileInfo(index).absolutePath()
//                       + "/" + index.data().toString();
//    qDebug() << "Set to current dir: " + path;
//    current_dir = QDir(path);
//}
//
//void Browser::unsetCurrentDir(const QModelIndex &index) {
//    auto path = model->fileInfo(index).absolutePath();
//    qDebug() << "Set to current dir: " + path;
//    current_dir = QDir(path);
//}
