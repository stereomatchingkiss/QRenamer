#include "renameFileThread.hpp"

#include <QDebug>
#include <QFile>
#include <QModelIndex>
#include <QString>
#include <QStringList>

renameFileThread::renameFileThread(QObject *parent) :
    QThread(parent),
    enable_revert_(false),
    new_file_names_(nullptr),
    source_indexes_(nullptr)
{   
}

/**
 * @brief setup the flag to indicate it is rename the\n
 * files or try to revert the renamed files
 *
 *
 * After the rename/revert process finish, the flag will be\n
 * set to false again automatic
 * @param value true : try to revert the renamed files;else false
 */
void renameFileThread::enable_revert(bool value) Q_DECL_NOEXCEPT
{
    enable_revert_ = value;
}

QStringList renameFileThread::get_error_message() const Q_DECL_NOEXCEPT
{
    return error_message_;
}

renameFileThread::Map renameFileThread::get_revert_map() const Q_DECL_NOEXCEPT
{
    return revert_map_;
}

void renameFileThread::set_dirs_to_scan(QStringList dirs) Q_DECL_NOEXCEPT
{
    dirs_to_scan_ = dirs;
}

void renameFileThread::set_new_file_names(QStringList *new_file_names) Q_DECL_NOEXCEPT
{
    new_file_names_ = new_file_names;
}

void renameFileThread::set_new_suffix(QStringList suffix) Q_DECL_NOEXCEPT
{
    new_suffix_ = suffix;
}

void renameFileThread::set_old_file_names(QStringList old_file_names) Q_DECL_NOEXCEPT
{
    old_file_names_ = old_file_names;
}

void renameFileThread::set_old_suffix(QStringList suffix) Q_DECL_NOEXCEPT
{
    old_suffix_ = suffix;
}

void renameFileThread::set_source_indexes(std::vector<QModelIndex> const &indexes) Q_DECL_NOEXCEPT
{
    source_indexes_ = &indexes;
}

void renameFileThread::rename(int Row)
{
    auto const OldName = dirs_to_scan_[Row] + "/" +
            old_file_names_[Row] + "." +
            old_suffix_[Row];
    if(QFile::exists(OldName)){
        auto const NewName = dirs_to_scan_[Row] + "/" +
                (*new_file_names_)[Row] + "." + new_suffix_[Row];
        if(!QFile::exists(NewName)){
            if(OldName != NewName && QFile::rename(OldName, NewName)){
                revert_map_.first.push_back(NewName);
                revert_map_.second.push_back(OldName);
            }else{
                error_message_.push_back(NewName + " can not rename");
            }
        }
    }else{
        //(*new_file_names_)[Row] = old_file_names_[Row];
        error_message_.push_back(OldName + " do not exist");
    }
}

void renameFileThread::run()
{   
    error_message_.clear();
    revert_map_.first.clear();
    revert_map_.second.clear();

    if(!enable_revert_){        
        for(decltype(source_indexes_->size()) i = 0; i
            != source_indexes_->size(); ++i){
            rename((*source_indexes_)[i].row());
            emit increment(i);
        }
    }else{
        //if revert, the fileNameModel will setup
        //the mapping data into old_file_names and
        //new_file_names
        for(decltype(old_file_names_.size()) i = 0;
            i != old_file_names_.size(); ++i){
            rename(i);
            emit increment(i);
        }
        enable_revert_ = false;
    }

    emit end();
}
