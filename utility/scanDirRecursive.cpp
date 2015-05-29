#include <QDir>
#include <QStringList>

#include <queue>

/**
 * @brief scan the directories under dir recursively
 * @param dir parent directory
 * @return all of the directories under dir
 */
QStringList scan_dir_recursive(QDir const &dir)
{
    std::queue<QString> queue;
    queue.push(dir.absolutePath());
    QStringList results;
    while (!queue.empty()) {
        auto const subdir_name = queue.front();
        queue.pop();
        results.push_back(subdir_name);
        QDir subdir(subdir_name);

        auto const &directories = subdir.entryInfoList({},
                                                       QDir::AllDirs | QDir::NoSymLinks | QDir::NoDotAndDotDot);
        for (auto const &data : directories) {
            queue.push(data.absoluteFilePath());
        }
    }

    return results;
}
