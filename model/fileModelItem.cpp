#include <QFileInfo>

#include "fileModelItem.hpp"

fileModelItem::fileModelItem()
{

}

fileModelItem::~fileModelItem()
{

}

void fileModelItem::add_new_file()
{
    dir_paths_.push_back("");
    old_suffix_.push_back("");
    new_suffix_.push_back("");
    old_base_name_.push_back("");
    new_base_name_.push_back("");
    old_file_name_complete_.push_back("");
}

void fileModelItem::add_new_file(const QString &input)
{
    QFileInfo const info(input);
    dir_paths_.push_back(info.absolutePath());
    old_suffix_.push_back(info.suffix());
    new_suffix_.push_back(old_suffix_.back());
    old_base_name_.push_back(info.completeBaseName());
    new_base_name_.push_back(old_base_name_.back());
    old_file_name_complete_.push_back(input);
}

void fileModelItem::remove_at(int row)
{
    dir_paths_.removeAt(row);
    old_suffix_.removeAt(row);
    new_suffix_.removeAt(row);
    new_base_name_.removeAt(row);
    old_base_name_.removeAt(row);
    old_file_name_complete_.removeAt(row);
}

