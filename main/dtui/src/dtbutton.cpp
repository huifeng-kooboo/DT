#include "dtbutton.h"
#include <QDebug>
#include <QEvent>
#include <QMouseEvent>


DTButton::DTButton(QWidget* pWidget):QPushButton(pWidget)
{
    setAttribute(Qt::WA_StyledBackground, true);
    setWindowFlag(Qt::FramelessWindowHint);
}


bool DTButton::event(QEvent *e)
{
    return QPushButton::event(e);
}

void DTButton::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event);
    return ;
}

void DTButton::mousePressEvent(QMouseEvent *e)
{
    QPushButton::mousePressEvent(e);
}

void DTButton::mouseMoveEvent(QMouseEvent *e)
{
    QPushButton::mouseMoveEvent(e);
}

void DTButton::mouseReleaseEvent(QMouseEvent *e)
{
    QPushButton::mouseReleaseEvent(e);
}

void DTButton::focusInEvent(QFocusEvent * e)
{
    QPushButton::focusInEvent(e);
}

void DTButton::focusOutEvent(QFocusEvent *e)
{
    QPushButton::focusOutEvent(e);
}

void DTButton::leaveEvent(QEvent *event)
{
    QPushButton::leaveEvent(event);

}

void DTButton::enterEvent(QEvent *event)
{
    QPushButton::enterEvent(event);

}
