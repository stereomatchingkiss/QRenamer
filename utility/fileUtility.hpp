#ifndef FILEUTILITY_HPP
#define FILEUTILITY_HPP

#include <QStringList>

void rename_files(QString const &dir, QStringList const &old_file_names,
                  QStringList const &new_file_names);

#endif // FILEUTILITY_HPP
