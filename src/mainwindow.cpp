#include "include/mainwindow.h"

#include <QDebug>

#include "interface/ui_browser.h"

MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent), ui(new Ui::MainWindow) {
    current_browser = nullptr;

    ui->setupUi(this);
    ui->lineSearch->setReadOnly(false);

    setTreeView();

    connect(ui->buttonModel, &QPushButton::pressed
            , this, &MainWindow::changeModel);
}

MainWindow::~MainWindow() {
    delete ui;
    delete current_browser;
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
    auto with_hidden = current_browser ? current_browser->withHidden() : false;
    auto browser = new ListBrowser(QDir::homePath(), with_hidden);
    if (current_browser) {
        auto widget_p = dynamic_cast<TreeBrowser*>(current_browser)->getView();
        ui->browser_layout->removeWidget(widget_p);
        delete current_browser;
    }
    ui->browser_layout->addWidget(browser->getView());

    current_browser = browser;
    browser_model = View::List;

    turnMoveButtons(true);

    connect(current_browser, &IBrowser::dirChanged
            , this, &MainWindow::printDirInfo);
    connect(ui->buttonHome, &QPushButton::pressed
            , current_browser, &IBrowser::jumpHome);
    connect(ui->buttonHidden, &QPushButton::clicked
            , current_browser, &IBrowser::turnVisibility);
    connect(ui->buttonBack, &QPushButton::clicked
            , browser, &ListBrowser::goBack);
//    connect(ui->buttonForward, &QPushButton::clicked
//            , browser, &ListBrowser::goForward);
    connect(ui->lineSearch, &QLineEdit::textChanged
            , current_browser, &IBrowser::filterRecords);

    printDirInfo(current_browser->getDirectoryInfo(
            current_browser->getRoot().path()));
}

void MainWindow::setTreeView() {
    auto with_hidden = current_browser ? current_browser->withHidden() : false;
    auto browser = new TreeBrowser(QDir::homePath(), with_hidden);

    if (current_browser) {
        auto widget_p = dynamic_cast<ListBrowser*>(current_browser)->getView();
        ui->browser_layout->removeWidget(widget_p);
        delete current_browser;
    }
    ui->browser_layout->addWidget(browser->getView());

    current_browser = browser;
    browser_model = View::Tree;

    turnMoveButtons(false);

    connect(current_browser, &IBrowser::dirChanged
            , this, &MainWindow::printDirInfo);
    connect(ui->buttonHome, &QPushButton::pressed
            , current_browser, &IBrowser::jumpHome);
    connect(ui->buttonHidden, &QPushButton::clicked
            , current_browser, &IBrowser::turnVisibility);
    connect(ui->lineSearch, &QLineEdit::textEdited
            , current_browser, &IBrowser::filterRecords);

    printDirInfo(current_browser->getDirectoryInfo(
            current_browser->getRoot().path()));
}

void MainWindow::turnMoveButtons(bool state) {
    ui->buttonBack->setEnabled(state);
    ui->buttonForward->setEnabled(state);
}

void MainWindow::printDirInfo(const QString &info) {
    ui->statusbar->showMessage(info);
}

void MainWindow::makeSearch() {
    current_browser->filterRecords(ui->lineSearch->text());
}
