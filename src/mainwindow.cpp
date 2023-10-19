#include <QFileSystemModel>
#include <QDebug>

#include "include/mainwindow.h"
#include "interface/ui_browser.h"

MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->browser->setSortingEnabled(true);
    ui->lineSearch->setReadOnly(false);
    auto model = new QFileSystemModel;
    model->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Hidden);
    model->setRootPath(QDir::homePath());
    ui->browser->setModel(model);
    ui->browser->setRootIndex(model->index(QDir::homePath()));
    connect(ui->browser, &QTreeView::expanded
            , this, &MainWindow::printChildInfo);
    connect(ui->browser, &QTreeView::collapsed
            , this, &MainWindow::printRootInfo);
    printDirectoryInfo(model->rootDirectory());
}

void MainWindow::printChildInfo(const QModelIndex &index) {
    auto model = dynamic_cast<const QFileSystemModel*>(ui->browser->model());
    auto dir_path = model->fileInfo(index).absolutePath()
                            + "/"
                            + index.data().toString();
    auto dir = QDir(dir_path);
    qDebug() << dir_path;
    printDirectoryInfo(dir);
}

void MainWindow::printRootInfo(const QModelIndex &index) {
    auto model = dynamic_cast<const QFileSystemModel*>(ui->browser->model());
    auto dir_path = model->fileInfo(index).absolutePath();
    auto dir = QDir(dir_path);
    qDebug() << dir_path;
    printDirectoryInfo(dir);
}

void MainWindow::printDirectoryInfo(const QDir &dir) {
    auto files_num = dir.entryList(QDir::Hidden | QDir::Files).count();
    auto dir_num = dir.entryList(QDir::Hidden
                                | QDir::Dirs
                                | QDir::NoDotAndDotDot).count();
    auto msg = dir.path() +
            QString(" Files: %1, Directories: %2").arg(files_num).arg(dir_num);
    ui->statusbar->showMessage(msg);
}

MainWindow::~MainWindow() {
    delete ui;
}
