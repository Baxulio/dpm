#ifndef SORTFILTERPROXYMODEL_H
#define SORTFILTERPROXYMODEL_H

#include <QDate>
#include <QSortFilterProxyModel>
#include <QAction>

class SortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    SortFilterProxyModel(QObject *parent = 0);

    QDate filterMinimumDate() const { return minDate; }
    void setFilterMinimumDate(const QDate &date);

    QDate filterMaximumDate() const { return maxDate; }
    void setFilterMaximumDate(const QDate &date);



protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const Q_DECL_OVERRIDE;
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const Q_DECL_OVERRIDE;

public slots:
    inline void setCaseSensitivity(bool b)
    {
        setFilterCaseSensitivity(b?Qt::CaseSensitive:Qt::CaseInsensitive);
    }
    inline void setRole(QAction *a)
    {
        setFilterRole(a->data().toInt());
    }

private:
    bool dateInRange(const QDate &date) const;

    QDate minDate;
    QDate maxDate;

};


#endif // SORTFILTERPROXYMODEL_H
