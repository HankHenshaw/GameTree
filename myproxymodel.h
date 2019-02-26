#ifndef MYPROXYMODEL_H
#define MYPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QModelIndex>

class MyProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit MyProxyModel(QObject *parent = nullptr);

private:
    virtual bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

    mutable QModelIndex prevIdx;
};

#endif // MYPROXYMODEL_H
