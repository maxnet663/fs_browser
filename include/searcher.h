#ifndef SEARCHER_H
#define SEARCHER_H

#include <QThreadPool>
#include <QRegExp>
#include <QDir>

class Searcher {

    QThreadPool thread_pool;

public:

    Searcher(QRegExp pattern, const QDir &dir);

};

class Task : QRunnable {
    const &
public:
    void run() override;
};

#endif //SEARCHER_H
