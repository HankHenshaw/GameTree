#ifndef TREEITEM_H
#define TREEITEM_H

#include <QList>
#include <QDebug>

class TreeItem
{
public:
    explicit TreeItem(const QString &data, TreeItem *parent = nullptr);
    ~TreeItem();

    TreeItem *child(int number);
    int childCount() const;
    QString data() const; // TODO: const QString& ???
    void insertChildren(TreeItem *item);
    TreeItem* parent();
    void setData(const QString &data);
    int childNumber() const;
    void removeChild(int row);
    const QList<TreeItem*>& getList() const;

private:
    QList<TreeItem*> m_childItems;
    TreeItem *m_parentItem;
    QString m_itemData;
};

#endif // TREEITEM_H
