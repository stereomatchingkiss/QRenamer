#ifndef FILTERDIALOG_HPP
#define FILTERDIALOG_HPP

#include <QDialog>
#include <QRegularExpression>

namespace Ui {
class filterDialog;
}

enum class fileNameHeader;
enum class filterType;

class filterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit filterDialog(QWidget *parent = nullptr);
    ~filterDialog();

    fileNameHeader get_filter_column() const Q_DECL_NOEXCEPT;
    QString get_filter_string() const Q_DECL_NOEXCEPT;
    filterType get_filter_type() const Q_DECL_NOEXCEPT;
    QRegularExpression::PatternOption get_filter_pattern() const Q_DECL_NOEXCEPT;

signals:
    void ok();

private slots:
    void on_cancelPushButton_clicked();

    void on_okPushButton_clicked();

private:
    Ui::filterDialog *ui;
};

#endif // FILTERDIALOG_HPP
