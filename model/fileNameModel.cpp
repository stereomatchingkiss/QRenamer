#include "fileNameModel.hpp"

#include <QDebug>
#include <QBrush>
#include <QRegularExpression>
#include <QtConcurrent>
#include <QVector>

#include <memory>
#include <vector>

#include "globalconst.hpp"
#include "../model/fileModelItem.hpp"
#include "../utility/initializer.hpp"
#include "../utility/stringUtility.hpp"
#include "../workerThreads/addDirThread.hpp"
#include "../workerThreads/renameFileThread.hpp"
#include "../workerThreads/scanDirThread.hpp"

fileNameModel::fileNameModel(QObject *parent) :
    QAbstractTableModel{parent},
    item_{new fileModelItem},
    add_dirs_thread_{new addDirThread{this}},
    rename_file_thread_{new renameFileThread{this}},
    scan_dir_thread_{new scanDirThread{this}}
{
    connect(scan_dir_thread_, &scanDirThread::scan_dir,
            this, &fileNameModel::scan_dir);
    connect(scan_dir_thread_, &scanDirThread::end,
            this, &fileNameModel::scan_dir_recursive_end_slot);
    connect(add_dirs_thread_, &addDirThread::increment,
            this, &fileNameModel::increment);
    connect(add_dirs_thread_, &addDirThread::end,
            this, &fileNameModel::add_dirs_recursive_end_slot);

    connect(rename_file_thread_, &renameFileThread::end,
            this, &fileNameModel::rename_file_finished);
    connect(rename_file_thread_, &renameFileThread::increment,
            this, &fileNameModel::increment);
}

fileNameModel::~fileNameModel()
{
    add_dirs_thread_->quit();
    rename_file_thread_->quit();
    scan_dir_thread_->quit();

    add_dirs_thread_->wait();
    rename_file_thread_->wait();
    scan_dir_thread_->wait();
}

void fileNameModel::add_dirs_recursive(const QString &dir_path)
{
    scan_dir_thread_->set_scan_dir(dir_path);
    scan_dir_thread_->start();
}

void fileNameModel::append_number_on_last_match(int length)
{    
    item_->new_base_name_ = prepend_symbol_on_match(item_->old_base_name_,
                                                    length,
                                                    //"(\\d+)[^\\d]*$"
                                                    //"(\\d+)(?!.*\\d)"
                                                    QRegularExpression("(\\d+)(?!.*\\d)"),
                                                    '0');
}

void fileNameModel::append_number_on_nth_match(int length, int position)
{    
    item_->new_base_name_ = prepend_symbol_on_nth_match(item_->old_base_name_,
                                                        length,
                                                        position,
                                                        QRegularExpression("(\\d+)"),
                                                        '0');
}

void fileNameModel::append_words(QString const &words)
{
    item_->new_base_name_ = item_->old_base_name_;
    QtConcurrent::blockingMap(item_->new_base_name_, [&words](QString &name)
    {
        name.append(words);
    });
}

int fileNameModel::columnCount(const QModelIndex&) const
{
    return static_cast<int>(fileNameHeader::LastElem);
}

void fileNameModel::clear_all()
{
    removeRows(0, item_->old_base_name_.size(), {});
}

QVariant fileNameModel::data(const QModelIndex &index, int role) const
{    
    switch(role){
    case Qt::DisplayRole:{
        switch (static_cast<fileNameHeader>(index.column())){
        case fileNameHeader::Path: {
            return item_->dir_paths_[index.row()];
        }
        case fileNameHeader::OldName: {
            return item_->old_base_name_[index.row()];
        }
        case fileNameHeader::NewName:{
            return item_->new_base_name_[index.row()];
        }
        case fileNameHeader::OldSuffix: {
            return item_->old_suffix_[index.row()];
        }
        case fileNameHeader::NewSuffix: {
            return item_->new_suffix_[index.row()];
        }
        default:{
            return {};
        }
        }
    }
    case Qt::ForegroundRole:{
        switch (static_cast<fileNameHeader>(index.column())){
        //NewName and OldName should use the same color
        case fileNameHeader::NewName:
        case fileNameHeader::OldName:{
            if(item_->new_base_name_[index.row()] == item_->old_base_name_[index.row()]){
                return QBrush(Qt::red);
            }else if(item_->match_regex_file_[index.row()]){
                return QBrush(Qt::blue);
            }
        }
        default:{
            return {};
        }
        }
    }
    }

    return {};
}

bool fileNameModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int,
                                 int, const QModelIndex&)
{
    if(action == Qt::CopyAction && data->hasUrls()){
        auto const Urls = data->urls();
        QStringList files;
        for(auto const &Url : Urls){
            QFileInfo const Info(Url.toLocalFile());
            if(Info.isFile()){
                files += Info.absoluteFilePath();
            }else if(Info.isDir()){
                QDir directory(Info.absoluteFilePath());
                files += directory.entryList(QDir::Files | QDir::NoDotAndDotDot);
                auto const AbsFilePath = Info.absoluteFilePath() + "/";
                for(QString &file : files){
                    file.prepend(AbsFilePath);
                }
            }
        }
        if(!files.isEmpty()){
            emit drop_data(files);
            return true;
        }
    }
    return false;
}

Qt::ItemFlags fileNameModel::flags(const QModelIndex &index) const
{
    return QAbstractTableModel::flags(index) |  Qt::ItemIsDropEnabled;
}

QStringList fileNameModel::get_rename_error_message() const Q_DECL_NOEXCEPT
{
    return rename_file_thread_->get_error_message();
}

QVariant fileNameModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole){
        if(orientation == Qt::Horizontal){
            switch(static_cast<fileNameHeader>(section)){
            case fileNameHeader::Path: {
                return QStringLiteral("Path");
            }
            case fileNameHeader::OldName: {
                return QStringLiteral("Original name");
            }
            case fileNameHeader::NewName: {
                return QStringLiteral("New name");
            }
            case fileNameHeader::OldSuffix: {
                return QStringLiteral("Original suffix");
            }
            case fileNameHeader::NewSuffix: {
                return QStringLiteral("New suffix");
            }
            default:{
                return {};
            }
            }
        }else if(orientation == Qt::Vertical){
            return section + 1;
        }
    }
    return {};
}

void fileNameModel::insert_at(int position, const QString &words)
{
    item_->new_base_name_ = item_->old_base_name_;
    QtConcurrent::blockingMap(item_->new_base_name_, [position, &words](QString &name)
    {
        name.insert(position, words);
    });
}

/**
 * @brief insert rows into the model
 * @param row row number begin to index
 * @param count how many rows need to insert
 * @return always true
 */
bool fileNameModel::insertRows(int row, int count, const QModelIndex&)
{
    if(item_->insert_file_name_.isEmpty()){
        beginInsertRows({}, row, row + count - 1);
        for(int i = 0; i != count; ++i){
            item_->add_new_file();
        }
        endInsertRows();
    }else if(item_->insert_file_name_.size() > row){
        beginInsertRows(QModelIndex(), row, row + count - 1);
        for(int i = row, size = item_->insert_file_name_.size();
            i != size; ++i){
            item_->add_new_file(item_->insert_file_name_[i]);
        }
        endInsertRows();
    }

    return true;
}

QStringList fileNameModel::mimeTypes() const
{
    return {"text/uri-list"};
}

/**
 * @brief add number into the files based on the string "$#"
 *
 *
 * ex : llvm$# will replace the string as\n
 * llvm000, llvm001, llvm002...
 * @param start start number, should not be negative value
 * @param increment increment step, should not be negative value
 * @param reset reset to start when the number reach reset number.\n
 * Should not be negative value
 * @param pad padding string, must be the same characters.\n
 * ex : 000, ###, 111 and so on
 */
void fileNameModel::numbering(int start, int increment,
                              int reset, const QString &pad)
{
    auto const BaseSize = item_->new_base_name_.size();
    auto const Symbol = !pad.isEmpty() ? pad[0] : QChar{'0'};
    auto const PadSize = pad.size() > 0 ? pad.size() : 1;
    auto const InitValue = start;
    for(decltype(item_->new_base_name_.size()) i = 0; i != BaseSize; ++i){
        auto const Number = QString("%1").arg(start, PadSize, 10,
                                              Symbol);
        item_->new_base_name_[i].replace("$#", Number);
        start += increment;
        if(reset != 0 && start > reset){
            start = InitValue;
        }
    }
}

void fileNameModel::prepend_words(const QString &words)
{
    item_->new_base_name_ = item_->old_base_name_;
    QtConcurrent::blockingMap(item_->new_base_name_, [&words](QString &name)
    {
        name.prepend(words);
    });
}

void fileNameModel::remove_at(int position, int n)
{
    item_->new_base_name_ = item_->old_base_name_;
    QtConcurrent::blockingMap(item_->new_base_name_, [position, n](QString &name)
    {
        name.remove(position, n);
    });
}

bool fileNameModel::removeRow(int row, const QModelIndex&)
{
    return removeRows(row, 1, {});
}

bool fileNameModel::removeRows(int row, int count, const QModelIndex&)
{    
    beginRemoveRows({}, row, row + count - 1);
    for(int i = 0; i != count; ++i){
        item_->remove_at(row);
    }
    endRemoveRows();

    return true;
}

void fileNameModel::rename_files()
{        
    rename_file_thread_->set_dirs_to_scan(item_->dir_paths_);
    rename_file_thread_->set_old_suffix(item_->old_suffix_);
    rename_file_thread_->set_old_file_names(item_->old_base_name_);
    rename_file_thread_->set_new_file_names(&(item_->new_base_name_));
    rename_file_thread_->set_new_suffix(item_->new_suffix_);
    rename_file_thread_->start();
}

void fileNameModel::replace_regex(const QRegularExpression &re, const QString &after)
{    
    if(re.pattern().isEmpty()){
        clear_match_regex_file();
        item_->new_base_name_ = item_->old_base_name_;
        return;
    }
    item_->new_base_name_ = item_->old_base_name_;
    for(decltype(item_->new_base_name_.size()) i = 0;
        i != item_->new_base_name_.size(); ++i){
        if(re.match(item_->new_base_name_[i]).hasMatch()){
            item_->new_base_name_[i].replace(re, after);
            item_->match_regex_file_[i] = true;
        }else{
            item_->match_regex_file_[i] = false;
        }
    }
}

void fileNameModel::replace_suffix(const QString &from,
                                   const QString &to)
{
    item_->new_suffix_ = item_->old_suffix_;
    QtConcurrent::blockingMap(item_->new_suffix_, [&from, &to](QString &name)
    {
        name.replace(from, to);
    });
}

void fileNameModel::replace_text(QString const &from, QString const &to)
{
    item_->new_base_name_ = item_->old_base_name_;
    QtConcurrent::blockingMap(item_->new_base_name_, [&from, &to](QString &name)
    {
        name.replace(from, to);
    });
}

void fileNameModel::revert_rename_result()
{       
    auto const RevertMap = rename_file_thread_->get_revert_map();
    clear_all();
    auto const &RenamedFile = RevertMap.first;
    auto const &RevertName = RevertMap.second;
    insert_rows_if_needed(RenamedFile.size(), 0);

    for(decltype(RenamedFile.size()) i = 0; i != RenamedFile.size(); ++i){
        QFileInfo const info(RenamedFile[i]);
        item_->dir_paths_[i] = info.absolutePath();
        item_->old_suffix_[i] = info.suffix();
        item_->old_base_name_[i] = info.completeBaseName();

        QFileInfo const new_info(RevertName[i]);
        item_->new_suffix_[i] = new_info.suffix();
        item_->new_base_name_[i] = new_info.completeBaseName();
    }

    rename_file_thread_->enable_revert();
    item_->source_indexes_.clear();
    rename_files();
}

int fileNameModel::rowCount(const QModelIndex&) const
{
    return item_->old_base_name_.size();
}

bool fileNameModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid() || role != Qt::DisplayRole){
        return false;
    }

    switch(static_cast<fileNameHeader>(index.column())){
    case fileNameHeader::Path:{
        item_->dir_paths_[index.row()] = value.value<QString>();
        break;
    }
    case fileNameHeader::OldName:{
        item_->old_base_name_[index.row()] = value.value<QString>();
        break;
    }
    case fileNameHeader::NewName:{
        item_->new_base_name_[index.row()] = value.value<QString>();
        break;
    }
    case fileNameHeader::OldSuffix:{
        item_->old_suffix_[index.row()] = value.value<QString>();
        break;
    }
    case fileNameHeader::NewSuffix:{
        item_->new_suffix_[index.row()] = value.value<QString>();
        break;
    }
    default:
        break;
    }

    return true;
}

void fileNameModel::set_selected_index(QVector<QModelIndex> indexes)
{
    item_->source_indexes_ = indexes;
    rename_file_thread_->set_source_indexes(indexes);
}

void fileNameModel::update_file(const QStringList &files)
{
    //make sure it provide strong exception guarantee
    if(!files.isEmpty()){
        item_->insert_file_name_ = item_->old_file_name_complete_ + files;
        item_->insert_file_name_.removeDuplicates();
        item_->match_regex_file_.clear();
        item_->match_regex_file_.resize(item_->insert_file_name_.size());
        std::fill(std::begin(item_->match_regex_file_),
                  std::end(item_->match_regex_file_), false);
        insert_rows_if_needed(item_->insert_file_name_.size(),
                              item_->dir_paths_.size());
        item_->insert_file_name_.clear();
    }
}

void fileNameModel::add_dirs_recursive_end_slot()
{
    auto const Results = add_dirs_thread_->get_old_file_name_complete();
    update_file(Results);

    emit add_dirs_recursive_end();
}

void fileNameModel::rename_file_finished()
{
    auto const NotRevert = !item_->source_indexes_.isEmpty();
    if(NotRevert){
        for(auto const &Index : item_->source_indexes_){
            auto const Row = Index.row();
            item_->old_base_name_[Row] = item_->new_base_name_[Row];
            item_->old_suffix_[Row] = item_->new_suffix_[Row];
        }
    }else{
        item_->old_base_name_ = item_->new_base_name_;
        item_->old_suffix_ = item_->new_suffix_;
    }
    emit rename_file_end();
}

void fileNameModel::scan_dir_recursive_end_slot()
{
    auto const dirs = scan_dir_thread_->get_result_dirs();
    if(!dirs.empty()){
        emit set_size(dirs.size());
        emit set_visible(true);
        add_dirs_thread_->set_dirs_to_scan(dirs);
        add_dirs_thread_->start();
    }else{
        emit add_dirs_recursive_end();
    }
}

void fileNameModel::clear_match_regex_file()
{
    std::fill(std::begin(item_->match_regex_file_),
              std::end(item_->match_regex_file_), false);
}

void fileNameModel::insert_data(const QStringList &input, fileNameHeader column)
{
    auto const Size = input.size();
    insert_rows_if_needed(Size, item_->dir_paths_.size());
    for(int i = 0; i != Size; ++i){
        setData(index(i, static_cast<int>(column)), input[i], Qt::DisplayRole);
    }
}

/**
 * @brief insert new rows if previous_size < current_size
 * @param current_size size of current data
 * @param previous_size size of previous data
 */
void fileNameModel::insert_rows_if_needed(int current_size, int previous_size)
{
    if(previous_size < current_size){
        insertRows(previous_size, current_size - previous_size, {});
    }
}
