#include "include/searcher.h"

Searcher::Searcher(QRegExp _pattern, const QDir &dir, bool _with_hidden)
: pattern(_pattern), search_root(dir), with_hidden(_with_hidden){
    thread_pool = QThreadPool::globalInstance();
    thread_pool->setMaxThreadCount(QThread::idealThreadCount());
}

void Searcher::start() {
    thread_pool->start(new Indexator(pattern, search_root, with_hidden));
    thread_pool->waitForDone();
}

void Seeker::run() {

}

void Indexator::run() {
    indexDir(dir);
}

void Indexator::indexDir(const QDir& _dir) {
    QFileInfoList dirs_list;
    if (with_hidden)
        dirs_list = _dir.entryInfoList(QDir::Dirs
                                 | QDir::NoDotAndDotDot
                                 | QDir::Hidden);
    else
        dirs_list = _dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    foreach(const auto &entry, dirs_list) {
        if (entry.isDir()) {
            thread_pool->start(new Seeker(pattern, entry.dir()), with_hidden);
            indexDir(entry.dir());
        }
    }
}