#ifndef DTGRAPHICSSCENE_H
#define DTGRAPHICSSCENE_H

// 重绘graphicsscene类
#include <QGraphicsScene>
#include <QVariant>

class DTGraphicsScene : public QGraphicsScene
{
    Q_OBJECT

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
};


#endif // DTGRAPHICSSCENE_H
