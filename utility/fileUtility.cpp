#include "fileUtility.hpp"

#include <QFile>

/**
 * @brief change the old file names to new file names
 * @param dir directory path of the files(old files and new files)
 * @param old_file_names name of the old files
 * @param new_file_names name of the new files
 */
void rename_files(QString const &dir, QStringList const &old_file_names, QStringList const &new_file_names)
{
    QString const temp = dir + "/";
    for(int i = 0, size = new_file_names.size(); i != size; ++i){
        QFile file(temp + old_file_names[i]);
        file.rename(temp + new_file_names[i]);
    }
}
