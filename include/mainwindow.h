#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QDir>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {

    Q_OBJECT
    Ui::MainWindow *ui;

public:

    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

public slots:

    void printChildInfo(const QModelIndex &index);

    void printRootInfo(const QModelIndex &index);

private:

    void printDirectoryInfo(const QDir &dir);
};
#endif //MAINWINDOW_H
