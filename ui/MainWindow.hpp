#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QStringList>

#include <functional>
#include <map>
#include <memory>

namespace Ui {
class MainWindow;
}

class filterDialog;
class fileNameModel;
class numberStep;
class quickCloseSignal;
class QQuickWidget;
class QTextBrowser;
class sortAndFilterFile;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    MainWindow(MainWindow const&) = delete;
    MainWindow& operator=(MainWindow const&) = delete;
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void add_dir_recursive_finished();    

    void close_help_reader();

    void drop_data(QStringList files);

    void enable_gui();

    void filter();

    void regex_replace_and_reset_view();
    void rename_file_fisnished();    

    void show_status_bar(QString message, int msec);

    void on_numberComboBox_currentTextChanged(const QString&);

    void on_numberSpinBox_valueChanged(int);

    void on_positionSpinBox_valueChanged(int);

    void on_prependLineEdit_textChanged(const QString&);

    void on_renameFileButton_clicked();

    void on_replaceFromLineEdit_textChanged(const QString&);

    void on_replaceTolineEdit_textChanged(const QString&);

    void on_replaceSuffixFromLineEdit_textChanged(const QString &arg1);

    void on_actionAddFolder_triggered();

    void on_actionRemoveAll_triggered();

    void on_actionAddFiles_triggered();

    void on_actionDeleteFiles_triggered();

    void on_appendLineEdit_textChanged(QString const&);

    void on_actionAddFolderRecursive_triggered();    

    void on_actionShowPath_triggered(bool);

    void on_actionShowSuffix_triggered(bool value);    

    void on_actionRevert_triggered(bool);

    void on_replaceSuffixTolineEdit_textChanged(const QString &arg1);

    void on_policyTabWidget_currentChanged(int index);

    void on_actionFilter_triggered(bool checked);

    void on_regexMatchlineEdit_textChanged(const QString&);

    void on_regexReplacelineEdit_textChanged(const QString&);

    void on_icaseCheckBox_clicked();

    void on_actionAboutQt_triggered();

    void on_insertAtSpinBox_valueChanged(int arg1);

    void on_insertWordsLineEdit_textChanged(const QString&);

    void on_removeAtSpinBox_valueChanged(int arg1);

    void on_removeRanageSpinBox_valueChanged(int);

    void on_numStepToolButton_clicked();

    void on_numRadioButton_clicked(bool checked);

    void on_actionRemovefilter_triggered();

    void on_actionHelp_triggered();

    void on_actionIcons_triggered();

    void on_actionReference_triggered();

    void on_lineEditChangeToFileName_textChanged(const QString &arg1);

    void on_spinBoxZeroFill_valueChanged(int arg1);

private:
    void add_directory(QString const &dir);
    void add_files();
    void append_words();
    void build_table();
    void build_connection();
    void change_name_with_increase_num();
    void enable_action_when_file_exist(bool value);
    void enable_delete_action(bool value);
    void enable_filter_action(bool value);
    void enable_remove_filter(bool value);
    void insert_words();
    std::vector<QModelIndex> map_proxy_index_to_source_index() const;
    void open_directory();
    void prepend_words();
    void regex_replace();
    void remove_words();
    void replace_suffix();
    void replace_text(); 
    void show_suffix(bool enable);
    bool view_is_empty() const Q_DECL_NOEXCEPT;

    void update_new_file_names();
    void update_number();    

private:            
    QString dir_path_;
    fileNameModel *file_model_;
    std::unique_ptr<quickCloseSignal> help_reader_;
    std::map<QString, std::function<void()>> rename_policy_;
    sortAndFilterFile *sort_filter_file_;

    filterDialog *filter_;
    numberStep *num_step_;
    Ui::MainWindow *ui;    
};

#endif // MAINWINDOW_HPP
