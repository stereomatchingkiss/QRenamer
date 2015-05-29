#ifndef SORTANDFILTERFILE_HPP
#define SORTANDFILTERFILE_HPP

#include <QSortFilterProxyModel>

#include <memory>

enum class fileNameHeader;
enum class filterType;

class QRegularExpression;

class sortAndFilterFile : public QSortFilterProxyModel
{
public:        
    explicit sortAndFilterFile(QObject *parent = nullptr);
    ~sortAndFilterFile();

    void set_filter_column(fileNameHeader header, bool invalidate = true);
    void set_filter_type(filterType type, bool invalidate = true);
    void set_regex(QRegularExpression reg, bool invalidate = true);

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;    

private:
    struct pimpl;
    std::unique_ptr<pimpl> impl_;
};

#endif // SORTANDFILTERFILE_HPP
