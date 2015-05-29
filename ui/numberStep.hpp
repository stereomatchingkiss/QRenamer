#ifndef NUMBERSTEP_HPP
#define NUMBERSTEP_HPP

#include <QDialog>

namespace Ui {
class numberStep;
}

class numberStep : public QDialog
{
    Q_OBJECT

public:
    explicit numberStep(QWidget *parent = 0);
    ~numberStep();

    int increment() const Q_DECL_NOEXCEPT;
    QString pad() const Q_DECL_NOEXCEPT;
    int reset() const Q_DECL_NOEXCEPT;
    int start() const Q_DECL_NOEXCEPT;

signals:
    void ok_button_clicked();

private slots:
    void on_cancelPushButton_clicked();

    void on_okPushButton_clicked();

    void on_numPadLineEdit_textEdited(const QString &arg1);

private:
    Ui::numberStep *ui;
};

#endif // NUMBERSTEP_HPP
