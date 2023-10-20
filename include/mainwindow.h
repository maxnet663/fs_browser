#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QDir>
#include <QListView>
#include <QTreeView>
#include <QFileSystemModel>

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
    bool show_hidden;
    QAbstractItemView *current_browser;
    View browser_model;
    QFileSystemModel *current_model;

public:

    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

public slots:

    void printChildInfo(const QModelIndex &index);

    void printRootInfo(const QModelIndex &index);

    void changeVisibility();

    void changeModel();

private:

    void printDirectoryInfo(const QDir &dir);

    void setListView();

    void setTreeView();

    QAbstractItemView *setBrowser(View type);
};
#endif //MAINWINDOW_H
