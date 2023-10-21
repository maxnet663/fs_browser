#ifndef SEARCHER_H
#define SEARCHER_H

#include <QThreadPool>
#include <QRegExp>
#include <QDir>

class Seeker : public QRunnable {

    const QRegExp &pattern;
    const QDir &dir;
    bool with_hidden;

public:

    Seeker(const QRegExp &_pattern, const QDir &_dir, bool _with_hidden = false)
    : pattern(_pattern), dir(_dir), with_hidden(_with_hidden) {}

    void run() override;
};

class Indexator : public QRunnable {

    QThreadPool *thread_pool;
    const QRegExp &pattern;
    const QDir &dir;
    bool with_hidden;

public:

    Indexator(const QRegExp &_pattern, const QDir &_dir, bool _with_hidden = false)
    : thread_pool(QThreadPool::globalInstance()), pattern(_pattern), dir(_dir)
    , with_hidden(_with_hidden) {}

    void run() override;

private:

    void indexDir(const QDir& dir);
};

class Searcher {

    QThreadPool *thread_pool;
    QRegExp pattern;
    const QDir &search_root;
    bool with_hidden;

public:

    Searcher(QRegExp _pattern, const QDir &dir, bool _with_hidden = false);

    void start();

};

#endif //SEARCHER_H
