#include "dtgraphicsview.h"
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QGraphicsView>

DTGraphicsView::DTGraphicsView(QGraphicsScene* pScene
                               ,QWidget*pWidget):QGraphicsView(pScene)
{
    // ToDo:设置相关的视图范围
    if(pWidget)
       setViewport(pWidget);
    setAttribute(Qt::WA_DeleteOnClose);
    setAttribute(Qt::WA_StyledBackground, true);
}


DTGraphicsView::DTGraphicsView(QWidget* pWidget_)
{
    //QGraphicsView::QGraphicsView();
}

void DTGraphicsView::setGraphicType(E_GRAPHICS_TYPE graphic_type)
{
    m_eGraphicsType = graphic_type;
    m_bSetGraphicsType = true;
}

bool DTGraphicsView::getGraphicType(E_GRAPHICS_TYPE &graphic_type)
{
    if(m_bSetGraphicsType)
    {
        graphic_type = m_eGraphicsType;
        return true;
    }
    else{
        return false;
    }
}

/**
  * @brief: 放大
*/
void DTGraphicsView::tool_ZoomIn()
{
    scale(1.2,1.2);
}

/**
  * @brief: 缩小
*/
void DTGraphicsView::tool_ZoomOut()
{
    scale(1/1.2,1/1.2);
}

/**
  * @brief: 旋转
*/
void DTGraphicsView::tool_Rotate()
{
    //todo
    // 默认每次旋转1.2
    rotate(1.2);
}

/**
  * @brief: 适应画布
*/
void DTGraphicsView::tool_AdapterToCanvas()
{
    //todo
}

bool DTGraphicsView::loadCanvas(QPixmap &qPixmap)
{
    QGraphicsScene *scene = new QGraphicsScene;
    scene->addPixmap(qPixmap);
    setScene(scene);
    return true;
}

void DTGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    // 发送Move事件
    QPointF pt =mapToScene(event->pos());
    emit positionChanged(pt.x(), pt.y());
    QGraphicsView::mouseMoveEvent(event);
}

void DTGraphicsView::paintEvent(QPaintEvent *event)
{
    QGraphicsView::paintEvent(event);
}

void DTGraphicsView::wheelEvent(QWheelEvent *event)
{
    QGraphicsView::wheelEvent(event);
}

void DTGraphicsView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
}

void DTGraphicsView::keyPressEvent(QKeyEvent *event)
{
    QGraphicsView::keyPressEvent(event);
}

void DTGraphicsView::dropEvent(QDropEvent *event)
{
    QGraphicsView::dropEvent(event);
}

void DTGraphicsView::focusInEvent(QFocusEvent *event)
{
    QGraphicsView::focusInEvent(event);
}

void DTGraphicsView::focusOutEvent(QFocusEvent *event)
{
    QGraphicsView::focusOutEvent(event);
}

void DTGraphicsView::showEvent(QShowEvent *event)
{
    QGraphicsView::showEvent(event);
}


