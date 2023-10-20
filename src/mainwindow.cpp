#include <QDebug>

#include "include/mainwindow.h"
#include "interface/ui_browser.h"

MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent), ui(new Ui::MainWindow), show_hidden(false)
, current_browser(nullptr) {
    ui->setupUi(this);
    ui->lineSearch->setReadOnly(false);

    current_model = new QFileSystemModel;
    current_model->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    current_model->setRootPath(QDir::homePath());

    setTreeView();

    printDirectoryInfo(current_model->rootDirectory());
    connect(ui->buttonHidden, &QPushButton::pressed
            , this, &MainWindow::changeVisibility);
    connect(ui->buttonModel, &QPushButton::pressed
            , this, &MainWindow::changeModel);
}

void MainWindow::printChildInfo(const QModelIndex &index) {
    auto dir_path = current_model->fileInfo(index).absolutePath()
                    + "/"
                    + index.data().toString();
    auto dir = QDir(dir_path);
    qDebug() << dir_path;
    printDirectoryInfo(dir);
}

void MainWindow::printRootInfo(const QModelIndex &index) {
    auto dir_path = current_model->fileInfo(index).absolutePath();
    auto dir = QDir(dir_path);
    qDebug() << dir_path;
    printDirectoryInfo(dir);
}

void MainWindow::printDirectoryInfo(const QDir &dir) {
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
            QString(" Files: %1, Directories: %2").arg(files_num).arg(dir_num);
    ui->statusbar->showMessage(msg);
}

void MainWindow::changeVisibility() {
    show_hidden = !show_hidden;
    if (show_hidden) {
        current_model->setFilter(QDir::AllEntries
                                 | QDir::NoDotAndDotDot
                                 | QDir::Hidden);
        ui->buttonHidden->setText("Hide Hidden");
    } else {
        current_model->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
        ui->buttonHidden->setText("Show Hidden");
    }
    printDirectoryInfo(current_model->rootDirectory());
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::changeModel() {
    switch (browser_model) {
        case View::Tree:
            setListView();
            break;
        case View::List:
            setTreeView();
            break;
        default:
            setTreeView();
    }
}

void MainWindow::setListView() {
    auto browser = new QListView(this);
    browser->setModel(current_model);
    browser->setRootIndex(current_model->index(current_model->rootDirectory().path()));
    if (current_browser) ui->browser_layout->removeWidget(current_browser);
    ui->browser_layout->addWidget(browser);
    browser_model = View::List;
}

void MainWindow::setTreeView() {
    auto browser = new QTreeView(this);
    browser->setModel(current_model);
    browser->setRootIndex(current_model->index(QDir::homePath()));
    browser->setSortingEnabled(true);
    browser->setColumnWidth(0, 250);
    browser->sortByColumn(0, Qt::SortOrder::AscendingOrder);

    if (current_browser) ui->browser_layout->removeWidget(current_browser);
    ui->browser_layout->addWidget(browser);
    current_browser = browser;
    browser_model = View::Tree;

    connect(browser, &QTreeView::expanded
            , this, &MainWindow::printChildInfo);
    connect(browser, &QTreeView::collapsed
            , this, &MainWindow::printRootInfo);
}
