#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H

#include <QLineEdit>
#include <QFileDialog>
#include <QFocusEvent>

class MyLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit MyLineEdit(QWidget *parent = nullptr);
protected:
    void focusInEvent(QFocusEvent* event);
};

#endif // MYLINEEDIT_H
