#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QDir>
#include <QListView>
#include <QListWidget>
#include <QTreeView>
#include <QTreeWidget>
#include <QFileSystemModel>

#include "include/browser.h"
#include "include/list_browser.h"
#include "include/tree_browser.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {

Q_OBJECT

    enum class View {
        Tree = 0,
        List = 1
    };

    Ui::MainWindow *ui;
    IBrowser *current_browser;
    View browser_model;

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

public slots:
    void changeModel();

    void printDirInfo(const QString &info);

private:
    void setListView();

    void setTreeView();

    void turnMoveButtons(bool state);

    QAbstractItemView *setBrowser(View type);
};
#endif //MAINWINDOW_H
