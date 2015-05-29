#include "scanDirThread.hpp"

#include <QDirIterator>

scanDirThread::scanDirThread(QObject *parent) :
    QThread(parent)
{    
}

QStringList scanDirThread::get_result_dirs() const Q_DECL_NOEXCEPT
{
    return result_dirs_;
}

/**
 * @brief setup the starting dir to scan
 * @param dir the starting dir to scan
 */
void scanDirThread::set_scan_dir(const QString dir) Q_DECL_NOEXCEPT
{
    dir_ = dir;
}

void scanDirThread::run()
{
    QDirIterator directories(dir_,
                             QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    QStringList dirs;
    while(directories.hasNext()){
        directories.next();
        dirs.push_back(directories.filePath());
        emit scan_dir(directories.filePath(), 2000);
    }

    result_dirs_ = dirs;
    emit end();
}
