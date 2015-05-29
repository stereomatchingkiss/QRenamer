#include "sortAndFilterFile.hpp"

#include "globalconst.hpp"

#include <QDebug>

#include <QRegularExpression>
#include <QRegularExpressionMatch>

struct sortAndFilterFile::pimpl
{
    pimpl();

    fileNameHeader filter_column_;
    filterType filter_type_;
    QRegularExpression reg_;
};

sortAndFilterFile::sortAndFilterFile(QObject *parent)
    : QSortFilterProxyModel(parent),
      impl_(new pimpl)
{
}

sortAndFilterFile::~sortAndFilterFile()
{

}

void sortAndFilterFile::set_filter_column(fileNameHeader header, bool invalidate)
{
    impl_->filter_column_ = header;
    if(invalidate){
        invalidateFilter();
    }
}

void sortAndFilterFile::set_filter_type(filterType type, bool invalidate)
{
    impl_->filter_type_ = type;
    if(invalidate){
        invalidateFilter();
    }
}

void sortAndFilterFile::set_regex(QRegularExpression reg, bool invalidate)
{
    if(reg.isValid()){
        impl_->reg_ = std::move(reg);
        if(invalidate){
            invalidateFilter();
        }
    }
}

bool sortAndFilterFile::filterAcceptsRow(int source_row,
                                         const QModelIndex &source_parent) const
{
    if(impl_->filter_column_ == fileNameHeader::LastElem){
        return QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);
    }

    auto const Col = static_cast<int>(impl_->filter_column_);
    auto const Index = sourceModel()->index(source_row, Col, source_parent);
    auto const Data = sourceModel()->data(Index).value<QString>();
    if(impl_->reg_.match(Data).hasMatch()){
        if(impl_->filter_type_ == filterType::Include){
            return true;
        }else{
            return false;
        }
    }else{
        if(impl_->filter_type_ == filterType::Include){
            return false;
        }else{
            return true;
        }
    }
}

bool sortAndFilterFile::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    auto const leftStr = sourceModel()->data(left).value<QString>();
    auto const rightStr = sourceModel()->data(right).value<QString>();

    return leftStr < rightStr;
}


sortAndFilterFile::pimpl::pimpl() :
    filter_column_(fileNameHeader::LastElem),
    filter_type_(filterType::Include)
{

}
