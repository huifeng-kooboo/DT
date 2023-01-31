#include "dtbutton.h"
#include <QDebug>
#include <QEvent>
#include <QMouseEvent>

// 默认按钮样式
//todo
#define DEFALUT_BUTTON_STYLE ""


DTButton::DTButton(QWidget* pWidget):QPushButton(pWidget)
{
    setAttribute(Qt::WA_StyledBackground, true);
    setWindowFlag(Qt::FramelessWindowHint);
    setStyleSheet(NORMAL_BUTTON_STYLE);

    Q_INIT_RESOURCE(dtui);
    QIcon closeIcon(":/resources/close_dark.png");
    QPixmap closePixmap = closeIcon.pixmap(20,21);
    m_image = closePixmap.toImage();
#ifdef TODO
#endif
}

void DTButton::setBtnRadius(int nRadius)
{
    this->setStyleSheet(styleSheet().append(QString(" QPushButton { border-radius: %2px;}").arg(objectName()).arg(nRadius)));
}

void DTButton::setBtnFont(const QFont &qFont)
{
    m_Font = qFont;
    this->setFont(qFont);
}

void DTButton::setBtnFontSize(int nPixel)
{
    m_Font.setPixelSize(nPixel);
    this->setFont(m_Font);
}

void DTButton::setBtnFixedSize(const QSize &qSize)
{
    this->setFixedSize(qSize);
}

void DTButton::setBtnStateColor(E_BUTTON_STATE state, const QString &qColor)
{
    switch (state) {
    case E_BUTTON_STATE::BUTTON_STATE_HOVER:
    {
        this->setStyleSheet(styleSheet().append(QString("QPushButton#%1:hover {background-color: %2;}").arg(objectName()).arg(qColor)));
        break;
    }
    case BUTTON_STATE_NORMAL:
    {
        this->setStyleSheet(styleSheet().append(QString("QPushButton#%1 {background-color: %2;}").arg(objectName()).arg(qColor)));
        break;
    }
    case BUTTON_STATE_DISABLE:
    {
        this->setStyleSheet(styleSheet().append(QString("QPushButton#%1:!enabled {background-color: %2;}").arg(objectName()).arg(qColor)));
        break;
    }
    case BUTTON_STATE_PRESSED:{
        this->setStyleSheet(styleSheet().append(QString("QPushButton#%1:pressed {background-color: %2;}").arg(objectName()).arg(qColor)));
        break;
    }
    default:
        break;
    }
}

void DTButton::setBtnTextStateColor(E_BUTTON_STATE state, const QString &qColor)
{
    switch (state) {
    case E_BUTTON_STATE::BUTTON_STATE_HOVER:
    {
        this->setStyleSheet(styleSheet().append(QString("QPushButton#%1:hover {color: %2;}").arg(objectName()).arg(qColor)));
        break;
    }
    case BUTTON_STATE_NORMAL:
    {
        this->setStyleSheet(styleSheet().append(QString("QPushButton#%1 {color: %2;}").arg(objectName()).arg(qColor)));
        break;
    }
    case BUTTON_STATE_DISABLE:
    {
        this->setStyleSheet(styleSheet().append(QString("QPushButton#%1:!enabled {color: %2;}").arg(objectName()).arg(qColor)));
        break;
    }
    case BUTTON_STATE_PRESSED:{
        this->setStyleSheet(styleSheet().append(QString("QPushButton#%1:pressed {color: %2;}").arg(objectName()).arg(qColor)));
        break;
    }
    default:
        break;
    }
}

bool DTButton::event(QEvent *e)
{
    return QPushButton::event(e);
}

void DTButton::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event);
    if(m_bNeedClose)
    {
        // 需要增加关闭按钮
        QPainter painter(this);
        int nWidth = this->width() -20;
        painter.drawImage(nWidth,11,m_image);
    }
    return ;
}

void DTButton::mousePressEvent(QMouseEvent *e)
{
    QPushButton::mousePressEvent(e);
    if(m_bNeedClose)
    {
        //
        QPoint pClickPoint = this->mapFromGlobal(QCursor::pos());
        if(pClickPoint.x() > this->width()-20)
        {
            emit signalCloseTab(this->objectName());
        }
    }

    if(!m_pressedIcon.isNull())
    {
        this->setIcon(m_pressedIcon);
    }

}

void DTButton::mouseMoveEvent(QMouseEvent *e)
{
    QPushButton::mouseMoveEvent(e);
}

void DTButton::mouseReleaseEvent(QMouseEvent *e)
{
    QPushButton::mouseReleaseEvent(e);
    if(!m_normalIcon.isNull())
    {
         this->setIcon(m_normalIcon);
    }
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
    if(!m_normalIcon.isNull())
    {
         this->setIcon(m_normalIcon);
    }
    if(isEnabled())
    {
        if(m_pHoverWidget && !(m_pHoverWidget->geometry().contains(QCursor::pos())))
        {
            m_pHoverWidget->setVisible(false);
        }
    }

}

void DTButton::enterEvent(QEvent *event)
{
    QPushButton::enterEvent(event);
    if(!m_hoverIcon.isNull())
    {
         this->setIcon(m_hoverIcon);
    }

    if(this->isEnabled())
    {
        if(m_pHoverWidget)
        {
            m_pHoverWidget->setGeometry(QCursor().pos().x() - m_pHoverWidget->width(),QCursor().pos().y(),m_pHoverWidget->width(),m_pHoverWidget->height());
            m_pHoverWidget->setVisible(true);
            m_pHoverWidget->show();
        }
    }

}
