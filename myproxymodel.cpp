#include "myproxymodel.h"
#include <QDebug>

MyProxyModel::MyProxyModel(QObject *parent): QSortFilterProxyModel(parent)
{
    prevIdx = QModelIndex();
}

bool MyProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
//    bool result = QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);
    QModelIndex currentIndex = sourceModel()->index(source_row, 0, source_parent);

    qDebug() << source_parent.row() << source_parent.column();
    qDebug() << source_parent.data();
    qDebug() << currentIndex.data();


//    if(prevIdx.parent() == currentIndex)
//    {
//        qDebug() << "-----------------";
//        return false;
//    }

//    if(sourceModel()->hasChildren(currentIndex))
//    {
//        for(int i = 0; i < sourceModel()->rowCount(currentIndex) && !result; ++i)
//        {
//            result = result || filterAcceptsRow(i, currentIndex);
//        }
//    }

    //TEST
//    prevIdx = currentIndex;

    return (sourceModel()->data(currentIndex).toString().contains(filterRegExp()));
//    return result;
}
