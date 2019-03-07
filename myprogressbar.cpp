#include "myprogressbar.h"

MyProgressBar::MyProgressBar(QWidget *parent): QProgressBar(parent)
{

}

bool MyProgressBar::event(QEvent *ev)
{
    if(ev->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent* mEvent = static_cast<QMouseEvent*>(ev);
        if(mEvent->button() == Qt::LeftButton)
        {
            emit signalMousePressedPos(mEvent->pos());
        }
    }
    else
        QProgressBar::event(ev);
    //TODO: Возвращаемое значение
}
