#include "addDirThread.hpp"

#include <QDir>

addDirThread::addDirThread(QObject *parent) :
    QThread(parent)
{       
}

QStringList addDirThread::get_old_file_name_complete() const
{
    return old_file_name_complete_;
}

void addDirThread::set_dirs_to_scan(const QStringList dirs)
{
    dirs_to_scan_ = dirs;
}

void addDirThread::run()
{
    QStringList old_file_name_complete;
    for(int i = 0, dir_size = dirs_to_scan_.size(); i != dir_size; ++i){
        QDir directory(dirs_to_scan_[i]);
        auto const file_infos = directory.entryInfoList({}, QDir::Files);
        for(int j = 0, file_size = file_infos.size(); j != file_size; ++j){
            old_file_name_complete.push_back(file_infos[j].absoluteFilePath());
        }
        emit increment(i);
    }

    old_file_name_complete_ = old_file_name_complete;
    emit end();
}
