#ifndef BROWSER_H
#define BROWSER_H

#include <QObject>
#include <QDir>
#include <QFileSystemModel>

/**
 * Interface for browsers. Defines signals, fields
 * and methods common to all browsers. Abstract
 */
class IBrowser : public QObject{

    Q_OBJECT
    QDir root_dir;
    bool show_hidden; // show hidden files and dirs?
    QDir current_dir;
    QFileSystemModel model;

public:
    IBrowser(const QDir &_root_dir = QDir::homePath(), bool _show_hidden = false);

    virtual ~IBrowser() = default;

    /**
     * Model getter
     * @return current model
     */
    QFileSystemModel *getModel() { return &model; }

    /**
     * Hidden flag getter
     * @return show hidden
     */
    bool withHidden() const { return show_hidden; }

    /**
     * Get current dir path and counts files and sirs in them
     * @param dir directory
     * @return String with path of dir and amount of files and dirs
     */
    QString getDirectoryInfo(const QDir &dir) const;

    /**
     * Rood dir getter
     * @return root dir
     */
    QDir getRoot() const { return root_dir; }

    /**
     * Current dir getter
     * @return root dir
     */
    QDir getCurrentDir() const { return current_dir; }

signals:
    /**
     * signals emits when current dir changed
     * @param info
     */
    void dirChanged(const QString &info);

public slots:
    /**
     * Change current visibility to show hidden records or not
     */
    void turnVisibility();

    /**
     * Sets current dir
     * @param dir new dir
     */
    void setCurrentDir(const QDir &dir);

    /**
     * Every browser model should implement behavior
     * when home button pressed
     */
    virtual void jumpHome() = 0;

    /**
     * Set filters to shown records in Browser
     * @param text
     */
    virtual void filterRecords(const QString &text);
};

#endif //BROWSER_H
