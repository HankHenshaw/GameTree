#include "mylineedit.h"

MyLineEdit::MyLineEdit(QWidget *parent) : QLineEdit (parent)
{

}

void MyLineEdit::focusInEvent(QFocusEvent *event)
{
    if(event->gotFocus())
    {
        QString str = QFileDialog::getOpenFileName(this, tr("Choose .exe file to add"), QString(), "*.exe");
        this->setText(str);
        this->clearFocus();
        if(!this->text().isEmpty())
        {
            this->setDisabled(true);
        }
        QFileDialog d;
    }
}
