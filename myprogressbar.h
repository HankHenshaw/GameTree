#ifndef MYPROGRESSBAR_H
#define MYPROGRESSBAR_H

#include <QProgressBar>
#include <QEvent>
#include <QMouseEvent>
#include <QDebug>

class MyProgressBar : public QProgressBar
{
    Q_OBJECT
public:
    explicit MyProgressBar(QWidget *parent = nullptr);
protected:
    virtual bool event(QEvent *ev) override;
signals:
    void signalMousePressedPos(QPoint);
};

#endif // MYPROGRESSBAR_H
