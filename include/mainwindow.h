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
    const QString root_dir;
    QDir current_dir;
    bool show_hidden;
    QAbstractItemView *current_browser;
    View browser_model;
    QFileSystemModel *current_model;

public:

    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

public slots:

    void printChildInfo(const QModelIndex &index);

    void printParentInfo(const QModelIndex &index);

    void changeVisibility();

    void changeModel();

    void changeDir(const QModelIndex &index);

    void setCurrentDir(const QModelIndex &index);

    void unsetCurrentDir(const QModelIndex &index);

    void jumpToHome();

private:

    void printDirectoryInfo(const QDir &dir);

    void setListView();

    void setTreeView();

    void turnMoveButtons(bool state);

    QAbstractItemView *setBrowser(View type);
};
#endif //MAINWINDOW_H
