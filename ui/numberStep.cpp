#include "numberStep.hpp"
#include "ui_numberstep.h"

#include <QMessageBox>

#include <algorithm>
#include <iterator>

numberStep::numberStep(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::numberStep)
{
    ui->setupUi(this);
}

numberStep::~numberStep()
{
    delete ui;
}

int numberStep::increment() const Q_DECL_NOEXCEPT
{
    return ui->numIncSpinBox->value();
}

QString numberStep::pad() const Q_DECL_NOEXCEPT
{
    return ui->numPadLineEdit->text();
}

int numberStep::reset() const Q_DECL_NOEXCEPT
{
    return ui->numResetSpinBox->value();
}

int numberStep::start() const Q_DECL_NOEXCEPT
{
    return ui->numStartSpinBox->value();
}

void numberStep::on_cancelPushButton_clicked()
{
    close();
}

void numberStep::on_okPushButton_clicked()
{
    emit ok_button_clicked();
}

void numberStep::on_numPadLineEdit_textEdited(const QString &arg1)
{
    if(!arg1.isEmpty()){
        auto const Target = arg1[0];
        auto const Func = [Target](decltype(Target) a){ return a == Target; };
        if(!std::all_of(std::begin(arg1), std::end(arg1), Func)){
            QMessageBox::warning(this, tr("Padding error"),
                                 tr("All of the padding characters should be the same"));
            auto replace = arg1;
            replace.replace(arg1[arg1.size() - 1], Target);
            ui->numPadLineEdit->setText(replace);
        }
    }else{
        QMessageBox::warning(this, tr("Padding error"), tr("Padding charaters should not be empty"));
        return;
    }
}
