#ifndef FILENAMEMODEL_HPP
#define FILENAMEMODEL_HPP

#include <QAbstractTableModel>
#include <QScopedPointer>
#include <QStringList>

enum class fileNameHeader;
enum class RenameType;

class addDirThread;
class fileModelItem;
class QRegularExpression;
class renameFileThread;
class scanDirThread;

/**
 * @brief The model in charge of file names manipulation
 *
 *
 * This class use QtConcurrent to process some string \n
 * but haven't do any benchmark yet.The main\n
 * reason I use it is because I want to get familiar with\n
 * the api of QtConcurrent but not performance.
 */
class fileNameModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit fileNameModel(QObject *parent = nullptr);
    ~fileNameModel() override;

    void add_dirs_recursive(QString const &dir_path);
    void append_number_on_last_match(int length);
    void append_number_on_nth_match(int length, int position);
    void append_words(QString const &words);
    void change_name_with_increase_num(QString const &change_file_name_to, int zero_fill);

    int columnCount(const QModelIndex &parent) const override;
    void clear_all();
    void clear_match_regex_file();

    QVariant data(const QModelIndex &index, int role) const override;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column,
                      const QModelIndex &parent) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    QStringList get_rename_error_message() const Q_DECL_NOEXCEPT;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    void insert_at(int position, QString const &words);
    bool insertRows(int row, int count, const QModelIndex &parent) override;

    QStringList mimeTypes() const override;

    void numbering(int start, int increment, int reset, QString const &pad);

    void prepend_words(QString const &words);

    void remove_at(int position, int n);
    bool removeRow(int row, const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    void rename_files();
    void replace_regex(QRegularExpression const &re, QString const &after);
    void replace_suffix(QString const &from, QString const &to);
    void replace_text(QString const &from, QString const &to);
    void revert_rename_result();
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    void set_selected_index(std::vector<QModelIndex> &&indexes);

    void update_file(QStringList const &files);

signals:
    void add_dirs_recursive_end();
    void drop_data(QStringList file);
    void increment(int);
    void rename_file_end();
    void scan_dir(QString dir, int msec);
    void set_size(int);
    void set_visible(bool);

private slots:
    void add_dirs_recursive_end_slot();
    void rename_file_finished();
    void scan_dir_recursive_end_slot();

private:
    void insert_data(QStringList const &input, fileNameHeader header);
    void insert_rows_if_needed(int current_size, int previous_size);

private:        
    QScopedPointer<fileModelItem> item_;

    addDirThread *add_dirs_thread_;
    renameFileThread *rename_file_thread_;
    scanDirThread *scan_dir_thread_;
};

#endif // FILENAMEMODEL_HPP
