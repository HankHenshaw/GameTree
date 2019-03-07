#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <QDebug>
#include "treeitem.h"

class TreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    TreeModel(QMap<QChar, int> &lettersList,QMap<QString, QSet<QString>> &gamesList,QObject *parent = nullptr); //explicit???
    ~TreeModel() override;

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    bool insertRows(int position, int rows, const QModelIndex& parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    TreeItem *getItem(const QModelIndex &index) const;
    TreeItem* getRoot() const;

private:
    TreeItem *m_rootItem;
};


#endif // TREEMODEL_H
