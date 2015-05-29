#include "filterDialog.hpp"
#include "ui_filterDialog.h"

#include "globalconst.hpp"

filterDialog::filterDialog(QWidget *parent) :
    QDialog{parent},
    ui{new Ui::filterDialog}
{
    ui->setupUi(this);
}

filterDialog::~filterDialog()
{
    delete ui;
}

fileNameHeader filterDialog::get_filter_column() const Q_DECL_NOEXCEPT
{
    if(ui->newNameRadioButton->isChecked()){
        return fileNameHeader::NewName;
    }else if(ui->originNameRadioButton->isChecked()){
        return fileNameHeader::OldName;
    }else if(ui->newSuffixRadioButton->isChecked()){
        return fileNameHeader::NewSuffix;
    }else if(ui->originSuffixRadioButton->isChecked()){
        return fileNameHeader::OldSuffix;
    }else if(ui->pathRadioButton->isChecked()){
        return fileNameHeader::Path;
    }

    return fileNameHeader::OldName;
}

QString filterDialog::get_filter_string() const Q_DECL_NOEXCEPT
{
    return ui->FilterlineEdit->text();
}

filterType filterDialog::get_filter_type() const Q_DECL_NOEXCEPT
{
    if(ui->excludeRadioButton->isChecked()){
        return filterType::Exclude;
    }else{
        return filterType::Include;
    }
}

QRegularExpression::PatternOption
filterDialog::get_filter_pattern() const Q_DECL_NOEXCEPT
{
    return ui->icaseCheckBox->isChecked() ?
                QRegularExpression::CaseInsensitiveOption :
                QRegularExpression::NoPatternOption;
}

void filterDialog::on_cancelPushButton_clicked()
{
    close();
}

void filterDialog::on_okPushButton_clicked()
{
    emit ok();
}
