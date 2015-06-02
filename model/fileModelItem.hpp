#ifndef FILEMODELITEM_HPP
#define FILEMODELITEM_HPP

#include <QFileInfo>
#include <QModelIndex>
#include <QStringList>
#include <QVector>

class fileModelItem
{
public:
    fileModelItem();
    ~fileModelItem();

    void add_new_file();
    void add_new_file(QString const &input);

    void remove_at(int row);

    QStringList dir_paths_;
    QStringList insert_file_name_;
    QStringList new_base_name_;
    QStringList new_suffix_;
    QStringList old_file_name_complete_;
    QStringList old_suffix_;
    QStringList old_base_name_;

    std::vector<QModelIndex> source_indexes_;
    QVector<bool> match_regex_file_;
};

#endif // FILEMODELITEM_HPP
