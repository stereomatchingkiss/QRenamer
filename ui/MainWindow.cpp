#include "filterDialog.hpp"
#include "MainWindow.hpp"
#include "numberStep.hpp"
#include "ui_MainWindow.h"

#include "globalconst.hpp"
#include "model/fileNameModel.hpp"

#include "modelProxy/sortAndFilterFile.hpp"

#include "utility/quickCloseSignal.hpp"

#include <QDir>
#include <QDebug>
#include <QFileDialog>
#include <QFileInfoList>
#include <QListView>
#include <QMessageBox>
#include <QSettings>
#include <QStringListModel>
#include <QtConcurrent>
#include <QTextBrowser>

namespace{

auto const Append = QStringLiteral("Append words");
auto const InsertWords = QStringLiteral("Insert words");
auto const Prepend = QStringLiteral("Prepend words");
auto const PrependZeroOnNumber = QStringLiteral("Prepend zero on number");
auto const RegexReplace = QStringLiteral("Regex");
auto const RemoveWords = QStringLiteral("Remove words");
auto const ReplaceBase = QStringLiteral("Replace words");
auto const ReplaceSuffix = QStringLiteral("Replace suffix");

}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow{parent},
    file_model_{new fileNameModel{this}},    
    sort_filter_file_{new sortAndFilterFile{this}},
    filter_{new filterDialog{this}},
    num_step_{new numberStep{this}},
    ui{new Ui::MainWindow}
{
    ui->setupUi(this);

    QSettings setting{"ThamSoftWare", "QRenamer"};
    restoreGeometry(setting.value("geometry").toByteArray());

    build_connection();
    build_table();

    sort_filter_file_->setSourceModel(file_model_);
    sort_filter_file_->setDynamicSortFilter(false);
    ui->fileView->setSortingEnabled(true);
    ui->fileView->setModel(sort_filter_file_);

    ui->fileView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->fileView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->fileView->setColumnHidden(static_cast<int>(fileNameHeader::Path), true);
    show_suffix(false);

    ui->numberComboBox->addItems(QStringList()<<"last number"<<"custom");
    ui->numberComboBox->setCurrentText(tr("last number"));

    ui->renameProgressBar->setVisible(false);
    ui->actionRevert->setEnabled(false);

    ui->numStepToolButton->setVisible(false);    
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QSettings setting{"ThamSoftWare", "QRenamer"};
    setting.setValue("geometry", saveGeometry());

    event->accept();
}

void MainWindow::drop_data(QStringList files)
{
    file_model_->update_file(files);
    update_new_file_names();
    enable_action_when_file_exist(true);
}

void MainWindow::add_dir_recursive_finished()
{    
    setEnabled(true);
    ui->renameProgressBar->setVisible(false);
    update_new_file_names();
    if(file_model_->rowCount()){
        enable_action_when_file_exist(true);
    }
}

void MainWindow::close_help_reader()
{
    help_reader_.reset(nullptr);
}

void MainWindow::enable_delete_action(bool value)
{
    ui->actionDeleteFiles->setEnabled(value);
    ui->actionRemoveAll->setEnabled(value);
}

void MainWindow::enable_filter_action(bool value)
{
    ui->actionFilter->setEnabled(value);
}

void MainWindow::enable_remove_filter(bool value)
{
    ui->actionRemovefilter->setEnabled(value);
}

void MainWindow::insert_words()
{
    file_model_->insert_at(ui->insertAtSpinBox->value(),
                           ui->insertWordsLineEdit->text());
}

void MainWindow::enable_gui()
{
    setEnabled(true);
    ui->renameProgressBar->setVisible(false);
}

void MainWindow::filter()
{        
    sort_filter_file_->set_regex(QRegularExpression{filter_->get_filter_string(),
                                 filter_->get_filter_pattern()},
                                 false);
    sort_filter_file_->set_filter_type(filter_->get_filter_type(), false);
    sort_filter_file_->set_filter_column(filter_->get_filter_column());    
    ui->fileView->selectAll();
    ui->renameFileButton->setEnabled(!view_is_empty());
    enable_remove_filter(true);
}

void MainWindow::regex_replace_and_reset_view()
{
    regex_replace();
    ui->fileView->reset();
}

void MainWindow::add_directory(QString const &dir)
{    
    QDir directory(dir);
    auto file_name = directory.entryList(QDir::Files);
    auto const Dir = dir + "/";
    QtConcurrent::blockingMap(file_name, [&Dir](QString &data)
    {
        data.prepend(Dir);
    });

    if(!file_name.isEmpty()){
        file_model_->update_file(file_name);
        update_new_file_names();        
        enable_action_when_file_exist(true);
    }
}

void MainWindow::add_files()
{
    auto const &temp = QFileDialog::getOpenFileNames(this, tr("Open files"),
                                                     dir_path_, QString(), nullptr,
                                                     QFileDialog::DontResolveSymlinks
                                                     );
    if(!temp.isEmpty()){
        dir_path_ = QFileInfo(temp[0]).absolutePath();
        file_model_->update_file(temp);        
        enable_action_when_file_exist(true);
    }
}

void MainWindow::append_words()
{
    file_model_->append_words(ui->appendLineEdit->text());
}

void MainWindow::build_connection()
{
    connect(filter_, &filterDialog::ok, this, &MainWindow::filter);

    connect(file_model_, &fileNameModel::drop_data,
            this, &MainWindow::drop_data);
    connect(file_model_, &fileNameModel::scan_dir,
            this, &MainWindow::show_status_bar);
    connect(file_model_, &fileNameModel::set_size,
            ui->renameProgressBar, &QProgressBar::setMaximum);
    connect(file_model_, &fileNameModel::set_visible,
            ui->renameProgressBar, &QProgressBar::setVisible);
    connect(file_model_, &fileNameModel::add_dirs_recursive_end,
            this, &MainWindow::add_dir_recursive_finished);

    connect(file_model_, &fileNameModel::rename_file_end,
            this, &MainWindow::rename_file_fisnished);
    connect(file_model_, &fileNameModel::increment,
            ui->renameProgressBar, &QProgressBar::setValue);

    connect(num_step_, &numberStep::ok_button_clicked, this,
            &MainWindow::regex_replace_and_reset_view);
}

void MainWindow::enable_action_when_file_exist(bool value)
{
    enable_delete_action(value);
    enable_filter_action(value);
    ui->renameFileButton->setEnabled(value);
}

void MainWindow::build_table()
{
    rename_policy_.emplace(Append, std::bind(&MainWindow::append_words, this));
    rename_policy_.emplace(InsertWords, std::bind(&MainWindow::insert_words, this));
    rename_policy_.emplace(Prepend, std::bind(&MainWindow::prepend_words, this));
    rename_policy_.emplace(PrependZeroOnNumber, std::bind(&MainWindow::update_number, this));
    rename_policy_.emplace(RegexReplace, std::bind(&MainWindow::regex_replace, this));
    rename_policy_.emplace(RemoveWords, std::bind(&MainWindow::remove_words, this));
    rename_policy_.emplace(ReplaceBase, std::bind(&MainWindow::replace_text, this));
    rename_policy_.emplace(ReplaceSuffix, std::bind(&MainWindow::replace_suffix, this));
}

std::vector<QModelIndex> MainWindow::map_proxy_index_to_source_index() const
{
    std::vector<QModelIndex> results;
    auto const Indexes = ui->fileView->selectionModel()->selectedRows();
    for(auto const &Index : Indexes){
        results.emplace_back(sort_filter_file_->mapToSource(Index));
    }

    return results;
}

/**
 * @brief enable the MainWindow after the rename process end
 */
void MainWindow::rename_file_fisnished()
{
    setEnabled(true);
    filter_->setEnabled(true);
    ui->renameProgressBar->setVisible(false);

    if(!file_model_->get_rename_error_message().isEmpty()){
        QStringListModel model(file_model_->get_rename_error_message());        
        QTableView view;
        view.setWindowTitle("Error messages");
        view.setModel(&model);
        view.horizontalHeader()->hide();

        QEventLoop loop;
        view.resizeColumnsToContents();
        view.resize(QSize{view.width(), view.height()});
        view.show();        
        loop.exec();                
    }

    ui->fileView->reset();
    if(file_model_->rowCount() != 0){
        enable_action_when_file_exist(true);
    }
}

void MainWindow::show_status_bar(QString message, int msec)
{
    statusBar()->showMessage(message, msec);
}

void MainWindow::open_directory()
{
    QFileDialog dialog(nullptr, tr("Open Directory"));
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setFileMode(QFileDialog::DirectoryOnly);
    dialog.setOption(QFileDialog::ShowDirsOnly);
    dialog.setOption(QFileDialog::DontResolveSymlinks);
    if(dialog.exec()){
        dir_path_ = dialog.selectedFiles()[0];
    }else{
        dir_path_.clear();
    }

    raise();
}

void MainWindow::prepend_words()
{
    file_model_->prepend_words(ui->prependLineEdit->text());
}

void MainWindow::regex_replace()
{   
    auto const Option = ui->icaseCheckBox->isChecked() ? QRegularExpression::CaseInsensitiveOption :
                                                         QRegularExpression::NoPatternOption;
    auto const Regex = QRegularExpression{ui->regexMatchlineEdit->text(), Option};
    if(Regex.isValid()){
        file_model_->replace_regex(Regex,
                                   ui->regexReplacelineEdit->text());
        if(ui->numRadioButton->isChecked()){
             file_model_->numbering(num_step_->start(),
                                    num_step_->increment(),
                                    num_step_->reset(),
                                    num_step_->pad());
        }
    }
}

void MainWindow::remove_words()
{
    file_model_->remove_at(ui->removeAtSpinBox->value(),
                           ui->removeRanageSpinBox->value());
}

void MainWindow::replace_text()
{
    file_model_->replace_text(ui->replaceFromLineEdit->text(),
                              ui->replaceTolineEdit->text());
}

void MainWindow::update_new_file_names()
{
    auto const RenamePolicy = ui->policyTabWidget->tabText(ui->policyTabWidget->currentIndex());
    auto const It = rename_policy_.find(RenamePolicy);
    if(It != std::end(rename_policy_)){
        It->second();
    }else{
        QMessageBox::warning(this, tr("Update fail"),
                             tr("Do not support this function or under construct"));
    }
}

/**
 * @brief update the view of new files, remember to call
 * "update_old_name_view" if the old file names have changed
 */
void MainWindow::update_number()
{
    if(ui->numberComboBox->currentText() == "last number"){
        file_model_->append_number_on_last_match(ui->numberSpinBox->value());
    }else{
        file_model_->append_number_on_nth_match(ui->numberSpinBox->value(),
                                                ui->positionSpinBox->value() - 1);
    }
}

void MainWindow::on_actionAddFiles_triggered()
{
    add_files();

    update_new_file_names();
}

void MainWindow::on_actionAddFolderRecursive_triggered()
{
    open_directory();
    if(!dir_path_.isEmpty()){
        setEnabled(false);
        file_model_->add_dirs_recursive(dir_path_);
    }
}

void MainWindow::on_actionAddFolder_triggered()
{    
    open_directory();
    if(!dir_path_.isEmpty()){
        add_directory(dir_path_);
    }

    update_new_file_names();
}

void MainWindow::on_actionDeleteFiles_triggered()
{
    auto *const model = ui->fileView->selectionModel();
    int offset = 0;
    for(auto const &var : model->selectedRows()){
        int const Index = var.row() - offset;
        file_model_->removeRow(Index, {});
        ++offset;
    }

    if(file_model_->rowCount() == 0){
        enable_action_when_file_exist(false);
    }
}

/**
 * @brief remove the names from the name views(old and new)
 */
void MainWindow::on_actionRemoveAll_triggered()
{
    file_model_->clear_all();
    ui->fileView->reset();    
    enable_action_when_file_exist(false);
}

void MainWindow::on_appendLineEdit_textChanged(const QString&)
{
    append_words();
    ui->fileView->reset();
}

void MainWindow::on_numberComboBox_currentTextChanged(QString const&)
{
    if(ui->numberComboBox->currentText() == "last number"){
        ui->positionSpinBox->setEnabled(false);
    }else{
        ui->positionSpinBox->setEnabled(true);
    }

    update_number();
    ui->fileView->reset();
}

void MainWindow::on_numberSpinBox_valueChanged(int)
{
    update_number();
    ui->fileView->reset();
}

void MainWindow::on_positionSpinBox_valueChanged(int)
{
    on_numberSpinBox_valueChanged(0);
}

void MainWindow::on_prependLineEdit_textChanged(const QString&)
{
    prepend_words();
    ui->fileView->reset();
}

/**
 * @brief rename the file in the other thread
 */
void MainWindow::on_renameFileButton_clicked()
{        
    setEnabled(false);
    filter_->setEnabled(false);

    ui->fileView->selectAll();
    auto source_indexes = map_proxy_index_to_source_index();
    ui->renameProgressBar->setVisible(true);
    ui->renameProgressBar->setRange(0, source_indexes.size());
    ui->actionRevert->setEnabled(true);
    ui->fileView->clearSelection();

    file_model_->set_selected_index(std::move(source_indexes));
    file_model_->rename_files();
}

void MainWindow::on_replaceFromLineEdit_textChanged(const QString&)
{
    replace_text();
    ui->fileView->reset();
}

void MainWindow::on_replaceTolineEdit_textChanged(const QString&)
{
    on_replaceFromLineEdit_textChanged(QStringLiteral(""));
}

void MainWindow::replace_suffix()
{
    file_model_->replace_suffix(ui->replaceSuffixFromLineEdit->text(),
                                ui->replaceSuffixTolineEdit->text());
}

void MainWindow::on_replaceSuffixFromLineEdit_textChanged(const QString&)
{
    replace_suffix();
    ui->fileView->reset();
}

void MainWindow::on_replaceSuffixTolineEdit_textChanged(const QString&)
{
    on_replaceSuffixFromLineEdit_textChanged(QString());
}

void MainWindow::show_suffix(bool enable)
{
    ui->fileView->setColumnHidden(static_cast<int>(fileNameHeader::OldSuffix),
                                  !enable);
    ui->fileView->setColumnHidden(static_cast<int>(fileNameHeader::NewSuffix),
                                  !enable);
}

/**
 * @brief detect the view has item or not
 *
 *
 * The model may not be empty because filtering\n
 * would not remove the items from the model
 * @return true if the view do not show any item;else false
 */
bool MainWindow::view_is_empty() const Q_DECL_NOEXCEPT
{
    ui->fileView->selectAll();
    auto const IsEmpty = ui->fileView->selectionModel()->selectedRows().isEmpty();
    ui->fileView->clearSelection();

    return IsEmpty;
}

void MainWindow::on_actionShowPath_triggered(bool)
{
    ui->fileView->setColumnHidden(static_cast<int>(fileNameHeader::Path),
                                  !ui->actionShowPath->isChecked());
}

void MainWindow::on_actionShowSuffix_triggered(bool value)
{
    ui->actionShowSuffix->setChecked(value);
    show_suffix(value);
}

void MainWindow::on_policyTabWidget_currentChanged(int index)
{
    auto const RenamePolicy = ui->policyTabWidget->tabText(index);
    if(RenamePolicy == ReplaceSuffix){
        on_actionShowSuffix_triggered(true);
    }else{
        on_actionShowSuffix_triggered(false);
    }
    file_model_->clear_match_regex_file();
    update_new_file_names();
    ui->fileView->reset();
}

void MainWindow::on_actionRevert_triggered(bool)
{
    ui->renameProgressBar->setRange(0, file_model_->rowCount());
    ui->renameProgressBar->setVisible(true);
    ui->actionRevert->setEnabled(false);
    setEnabled(false);
    file_model_->revert_rename_result();
}

void MainWindow::on_actionFilter_triggered(bool)
{
    filter_->show();
}

void MainWindow::on_regexMatchlineEdit_textChanged(const QString&)
{
    regex_replace_and_reset_view();
}

void MainWindow::on_regexReplacelineEdit_textChanged(const QString&)
{
    on_regexMatchlineEdit_textChanged("");
}

void MainWindow::on_icaseCheckBox_clicked()
{
    on_regexMatchlineEdit_textChanged("");
}

void MainWindow::on_actionAboutQt_triggered()
{
    QMessageBox::aboutQt(this);
}

void MainWindow::on_insertAtSpinBox_valueChanged(int)
{
    insert_words();
    ui->fileView->reset();
}

void MainWindow::on_insertWordsLineEdit_textChanged(const QString&)
{
    on_insertAtSpinBox_valueChanged(0);
}

void MainWindow::on_removeAtSpinBox_valueChanged(int)
{
    remove_words();
    ui->fileView->reset();
}

void MainWindow::on_removeRanageSpinBox_valueChanged(int)
{
    on_removeAtSpinBox_valueChanged(0);
}

void MainWindow::on_numStepToolButton_clicked()
{
    num_step_->exec();
}

void MainWindow::on_numRadioButton_clicked(bool checked)
{
    ui->numStepToolButton->setVisible(checked);
    regex_replace_and_reset_view();
}

void MainWindow::on_actionRemovefilter_triggered()
{
    sort_filter_file_->set_regex(QRegularExpression{""}, false);
    sort_filter_file_->set_filter_type(filterType::Include, false);
    sort_filter_file_->set_filter_column(fileNameHeader::OldName);
    enable_remove_filter(false);
    ui->renameFileButton->setEnabled(!view_is_empty());
}

void MainWindow::on_actionHelp_triggered()
{
    auto const LOCATION = QStringLiteral("qrc:/qml/Main.qml");

    help_reader_.reset(new quickCloseSignal);

    connect(help_reader_.get(), &quickCloseSignal::widget_close, this,
            &MainWindow::close_help_reader);

    help_reader_->setSource(QUrl(LOCATION));
    help_reader_->setResizeMode(QQuickWidget::SizeRootObjectToView);
    help_reader_->setWindowTitle(tr("Help menu"));
    help_reader_->show();
}

void MainWindow::on_actionIcons_triggered()
{
    QMessageBox::information(this, tr("Source"), tr("The icons are come from http://www.fatcow.com/free-icons"));
}

void MainWindow::on_actionReference_triggered()
{
    QMessageBox::information(this, tr("Reference"),
                             tr("The regex functions of this app is reference to regexrenamer(http://regexrenamer.sourceforge.net/),\n"
                                "many functions and tutorials are inspired by it"));
}
