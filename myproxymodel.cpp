#include "myproxymodel.h"
#include <QDebug>

MyProxyModel::MyProxyModel(QObject *parent): QSortFilterProxyModel(parent)
{

}

bool MyProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    bool result = QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);
    QModelIndex currentIndex = sourceModel()->index(source_row, 0, source_parent);
    if(sourceModel()->hasChildren(currentIndex))
    {
        for(int i = 0; i < sourceModel()->rowCount(currentIndex) && !result; ++i)
        {
            result = result || filterAcceptsRow(i, currentIndex);
        }
    }
    return result;
}

bool MyProxyModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(role != Qt::EditRole)
        return false;

    bool success;
    success = sourceModel()->setData(index, value, role);

    emit dataChanged(mapFromSource(index), mapFromSource(index));
    return success;
}

bool MyProxyModel::insertRows(int row, int count, const QModelIndex &parent)
{
    bool success;

    beginInsertRows(parent, row, row + count - 1);
    success = sourceModel()->insertRows(row, count, mapToSource(parent));
    endInsertRows();
    return true;
}

bool MyProxyModel::removeRows(int row, int count, const QModelIndex &parent)
{
    bool success;

    beginRemoveRows(parent, row, row + count - 1);
    qDebug() << "Start Proxy remove";
    qDebug() << parent.data();
    success = sourceModel()->removeRow(row, mapToSource(parent));
    qDebug() << "End Proxy remove";
    endRemoveRows();

    return true;
}
