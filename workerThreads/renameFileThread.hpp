#ifndef RENAMEFILETHREAD_HPP
#define RENAMEFILETHREAD_HPP

#include <QModelIndex>

#include <QObject>
#include <QThread>

#include <QStringList>

class renameFileWorker;

class renameFileThread : public QThread
{
    Q_OBJECT
public:
    using Map = std::pair<QStringList,QStringList>;

    explicit renameFileThread(QObject *parent = nullptr);    
    renameFileThread& operator=(renameFileThread const &) = delete;
    renameFileThread(renameFileThread const&) = delete;

    void enable_revert(bool value = true) Q_DECL_NOEXCEPT;

    QStringList get_error_message() const Q_DECL_NOEXCEPT;
    Map get_revert_map() const Q_DECL_NOEXCEPT;

    void set_dirs_to_scan(QStringList dirs) Q_DECL_NOEXCEPT;
    void set_new_file_names(QStringList *new_file_names) Q_DECL_NOEXCEPT;
    void set_new_suffix(QStringList suffix) Q_DECL_NOEXCEPT;
    void set_old_file_names(QStringList old_file_names) Q_DECL_NOEXCEPT;
    void set_old_suffix(QStringList suffix) Q_DECL_NOEXCEPT;
    void set_source_indexes(QVector<QModelIndex> indexes) Q_DECL_NOEXCEPT;

    void rename(int Row);
signals:
    void end();
    void increment(int value);

private:
    void run() override;

private:    
    QStringList dirs_to_scan_;
    bool enable_revert_;
    QStringList error_message_;
    QStringList *new_file_names_;
    QStringList new_suffix_;
    QStringList old_file_names_;    
    QStringList old_suffix_;
    std::pair<QStringList,QStringList> revert_map_;

    //if not revert, renameFileThread have to
    //build up the revert map and make sure the
    //indexes store the row number of source
    //but not the row number of proxy model
    //This is the reason why source_index_ exist
    QVector<QModelIndex> source_indexes;
};

#endif // RENAMEFILETHREAD_HPP
