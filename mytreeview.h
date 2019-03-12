#ifndef MYTREEVIEW_H
#define MYTREEVIEW_H

#include <QTreeView>
#include <QKeyEvent>

class MyTreeView : public QTreeView
{
    Q_OBJECT
public:
    MyTreeView(QWidget *parent = nullptr);
protected:
    virtual void keyPressEvent(QKeyEvent *event);
signals:
    void signalKeyDelete();
    void signalKeyEnter();
};

#endif // MYTREEVIEW_H
