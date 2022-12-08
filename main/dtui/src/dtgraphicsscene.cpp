#include "dtgraphicsscene.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGuiApplication>
#include <QScreen>
#include <QColor>
#include <QRgb>
void DTGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    auto pos = mouseEvent->lastScenePos();
    QPixmap tempPix = QGuiApplication::screenAt(QPoint(QCursor::pos().x(),QCursor::pos().y()))->grabWindow(0,QCursor::pos().x(),QCursor::pos().y(),1,1);    // 获取坐标值位置处的像素图

    // @brief: 构造需要发送的数据
    QMap<QString,QVariant> mapResult;
    mapResult.insert("pos_x", pos.x());
    mapResult.insert("pos_y", pos.y());
    QColor  color = tempPix.toImage().pixel(0,0);
    mapResult.insert("color",color);

    emit signalMouseMove(mapResult);
    QGraphicsScene::mouseMoveEvent(mouseEvent);
}

