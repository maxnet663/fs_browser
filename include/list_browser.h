#ifndef LISTBROWSER_H
#define LISTBROWSER_H

#include <QListView>
#include <QStringList>

#include "include/browser.h"
#include <QSortFilterProxyModel>

class ListBrowser : public IBrowser {

    Q_OBJECT
    QListView view;
    QStringList pathCache; // stores the travel path for moving using the forward and backward buttons

public:
    ListBrowser(const QDir &root_dir = QDir::homePath()
                , bool _show_hidden = false);

    ~ListBrowser() override = default;

    /**
     * View getter
     * @return pointer to view
     */
    QListView *getView() { return &view; }

public slots:
    /**
     * Method for moving between directories
     * @param index
     */
    void changeDir(const QModelIndex &index);

    /**
     * Moves to rood dir
     */
    void jumpHome() override;

    /**
     * Moves to previous dir
     */
    void goBack();

    /**
     * Moves to next dir in case you have been to there
     */
    void goForward(); // todo
};

#endif //LISTBROWSER_H
