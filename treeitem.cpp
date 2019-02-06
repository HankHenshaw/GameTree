#include "treeitem.h"

TreeItem::TreeItem(const QString &data, TreeItem *parent)
{
    m_itemData = data;
    m_parentItem = parent;
}

TreeItem::~TreeItem()
{
    qDeleteAll(m_childItems);
}

TreeItem *TreeItem::child(int number)
{
    return m_childItems.value(number);
}

int TreeItem::childCount() const
{
    return m_childItems.count();
}

QString TreeItem::data() const
{
    return m_itemData;
}

void TreeItem::insertChildren(TreeItem *item)
{
    //TODO
    m_childItems.append(item);
}

TreeItem* TreeItem::parent()
{
    return m_parentItem;
}

void TreeItem::setData(const QString &data)
{
    m_itemData = data;
}

int TreeItem::childNumber() const
{
    if(m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<TreeItem*>(this));

    return 0;
}
