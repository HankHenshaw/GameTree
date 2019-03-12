#include "mytreeview.h"

MyTreeView::MyTreeView(QWidget *parent) : QTreeView (parent)
{

}

void MyTreeView::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Delete)
    {
        emit signalKeyDelete();
    }
    else if(event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
    {
        emit signalKeyEnter();
    }
    else
    {
        QTreeView::keyPressEvent(event);
    }
}
