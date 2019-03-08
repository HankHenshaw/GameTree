#include "treemodel.h"

TreeModel::TreeModel(QMap<QChar, int> &lettersList, QMap<QString, QSet<QString> > &gamesList, QObject *parent) : QAbstractItemModel(parent)
{
    QString rootData("Title");
    m_rootItem = new TreeItem(rootData);

    //Устнановка данных

    QList<TreeItem*> parents;
    parents << m_rootItem;

    QMap<QChar, int>::iterator lettersBeginIterator = lettersList.begin();
    QMap<QChar, int>::iterator lettersEndIterator = lettersList.end();

    QMap<QString, QSet<QString>>::iterator gamesBeginIterator = gamesList.begin();

    //Позиция родителя 0 ур-ня вложенности(не считая корня)
    int parentNumber = 0;

    while(lettersBeginIterator != lettersEndIterator)
    {
        //Добавляем буквы (0 уровень вложенности, если не считать корень)
        parents.last()->insertChildren(new TreeItem(lettersBeginIterator.key()));

        //Получаем кол-во игр в данной секции
        int numberOfParticularGames = lettersBeginIterator.value();

        //Счетчик игр
        int counterOfGames = 0;

        //Позиция родителя 1 ур-ня вложенности(подродителя)
        int subParentNumber = 0;

        while(counterOfGames < numberOfParticularGames)
        {
            //Итераторы по подпозициям в зависимости от позиции
            QSet<QString>::iterator subGamesBeginIterator = gamesBeginIterator.value().begin();
            QSet<QString>::iterator subGamesEndIterator = gamesBeginIterator.value().end();

            //Добавляем ребенка к родителю 0 ур-ня
            parents.last()->child(parentNumber)->insertChildren(new TreeItem(gamesBeginIterator.key(), parents.last()->child(parentNumber)));

            //Увеличиваем счетчик кол-ва игр начинающихся на данную букву на 1
            ++counterOfGames;

            //Увеличиваем итератор прохода по подциклу
            ++gamesBeginIterator;

            //Цикл по подпозициям
            //Возможно есть смысл сделать тоже отдельный счетчик для подпозиций
            while(subGamesBeginIterator != subGamesEndIterator)
            {
                //Добавляем ребенка к родителю 1 ур-ня если строка не пустая
                if(!(*subGamesBeginIterator).isEmpty())
                    parents.last()->child(parentNumber)->child(subParentNumber)->insertChildren(new TreeItem(*subGamesBeginIterator, parents.last()->child(parentNumber)->child(subParentNumber)));

                //Увеличиваем итератор прохода по подподциклу
                ++subGamesBeginIterator;
            }

            //Увеличиваем позицию подродителя
            ++subParentNumber;
        }

        //Увеличиваем позицию родителя на 1
        ++parentNumber;

        //Увеличиваем итератор прохода по циклу
        ++lettersBeginIterator;
    }
}

TreeModel::~TreeModel()
{
    delete m_rootItem;
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if(role != Qt::DisplayRole)
        return QVariant();

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

    return item->data();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if(!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem *parentItem;

    if(!parent.isValid())
        parentItem = m_rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem *childItem = parentItem->child(row);
    if(childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if(!index.isValid())
        return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem->parent();

    if(parentItem == nullptr)
        return QModelIndex();

    return createIndex(parentItem->childNumber(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem;
    if(parent.column() > 0)
        return 0;

    if(!parent.isValid())
        parentItem = m_rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());
    return parentItem->childCount();
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return 1;
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return nullptr;

    return QAbstractItemModel::flags(index);
}

bool TreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(role != Qt::EditRole)
        return false;

    TreeItem *item = getItem(index);
    item->setData(value.toString());

    emit dataChanged(index, index);
    return true;
}

bool TreeModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    TreeItem *parentItem = getItem(parent);

    layoutAboutToBeChanged();
    beginInsertRows(parent, position, position + rows - 1);
    if(parent.isValid())
        parentItem->insertChildren(new TreeItem("", getItem(parent)));
    else
        parentItem->insertChildren(new TreeItem(""));
    endInsertRows();
    layoutChanged();

    return true;
}

bool TreeModel::removeRows(int row, int count, const QModelIndex &parent)
{
    qDebug() << "Start model remove";
    qDebug() << parent.data();
    layoutAboutToBeChanged();
    beginRemoveRows(parent, row, row + count -1);
    int parentsAmount = m_rootItem->childCount();
    QString itemData = parent.data().toString();

    for(int parentsCount = 0; parentsCount < parentsAmount; ++parentsCount)
    {
        if(m_rootItem->child(parentsCount)->data() == itemData)
        {
            qDebug() << "Match!";
            m_rootItem->removeChild(parentsCount);
            break;
        }

        bool isFound = false;

        int childrenAmount = m_rootItem->child(parentsCount)->childCount();
        for(int childrenCount = 0; childrenCount < childrenAmount; ++childrenCount)
        {
            if(m_rootItem->child(parentsCount)->child(childrenCount)->data() == itemData)
            {
                qDebug() << "Match!";
                m_rootItem->child(parentsCount)->removeChild(childrenCount);
                isFound = true;
                break;
            }

            int grandChildrenAmount = m_rootItem->child(parentsCount)->child(childrenCount)->childCount();
            for(int grandChildrenCount = 0; grandChildrenCount < grandChildrenAmount; ++grandChildrenCount)
            {
                if(m_rootItem->child(parentsCount)->child(childrenCount)->child(grandChildrenCount)->data() == itemData)
                {
                    qDebug() << "Match!";
                    m_rootItem->child(parentsCount)->child(childrenCount)->removeChild(grandChildrenCount);
                    isFound = true;
                    break;
                }
            }

            if(isFound)
                break;
        }

        if(isFound)
            break;
    }

    qDebug() << "End model remove";
    endRemoveRows();
    qDebug() << "endRemoveRows";
    layoutChanged();
    qDebug() << "layoutChanged";
    return true;
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(section);

    if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return m_rootItem->data();

    return QVariant();
}

TreeItem *TreeModel::getRoot() const
{
    return m_rootItem;
}

TreeItem *TreeModel::getItem(const QModelIndex &index) const
{
    if(index.isValid())
    {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        if(item)
            return item;
    }

    TreeItem *root = getRoot();
    return root;
}
