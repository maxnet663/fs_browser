#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QListView>
#include <QTreeView>

#include "include/browser.h"
#include "include/list_browser.h"
#include "include/tree_browser.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {

    Q_OBJECT

    /**
     * ID for current browser
     */
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
    /**
     * changes current model
     */
    void changeModel();

    /**
     * Prints dir info to status bar
     * @param info
     */
    void printDirInfo(const QString &info);

private:
    /**
     * Sets ListView to current browser
     */
    void setListView();

    /**
     * Sets TreeView to current browser
     */
    void setTreeView();

    /**
     * Change availability for back and forward buttons
     * @param state
     */
    void turnMoveButtons(bool state);
};
#endif //MAINWINDOW_H
