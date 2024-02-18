#ifndef DTUNDOCOMMAND_H
#define DTUNDOCOMMAND_H

// 撤回消息
#include <QUndoCommand>
#include "dtgraphicsitem.h"

class MoveShapeCommand : public QUndoCommand
{
public:
    MoveShapeCommand(QGraphicsScene *graphicsScene, const QPointF & delta ,
                QUndoCommand * parent = 0);
    MoveShapeCommand(QGraphicsItem * item, const QPointF & delta , QUndoCommand * parent = 0);
    void undo() Q_DECL_OVERRIDE;
    void redo() Q_DECL_OVERRIDE;
private:
    QGraphicsScene *m_myGraphicsScene;
    QGraphicsItem  *m_myItem;
    QList<QGraphicsItem *> m_myItems;
    QPointF m_myDelta;
    bool m_bMoved;
};

class ResizeShapeCommand : public QUndoCommand
{
public:
    enum { Id = 1234, };
    ResizeShapeCommand(QGraphicsItem * item ,
                       int handle,
                       const QPointF& scale,
                       QUndoCommand *parent = 0 );
    void undo() Q_DECL_OVERRIDE;
    void redo() Q_DECL_OVERRIDE;

    bool mergeWith(const QUndoCommand *command) Q_DECL_OVERRIDE;
    int id() const Q_DECL_OVERRIDE { return Id; }
private:
    QGraphicsItem  *m_myItem;
    int m_handle_;
    int m_opposite_;
    QPointF m_scale_;
    bool m_bResized;
};

class ControlShapeCommand : public QUndoCommand
{
public:
    enum { Id = 1235, };
    ControlShapeCommand(QGraphicsItem * item ,
                       int handle,
                       const QPointF& newPos,
                       const QPointF& lastPos,
                       QUndoCommand *parent = 0 );
    void undo() Q_DECL_OVERRIDE;
    void redo() Q_DECL_OVERRIDE;

    bool mergeWith(const QUndoCommand *command) Q_DECL_OVERRIDE;
    int id() const Q_DECL_OVERRIDE { return Id; }

private:
    QGraphicsItem  *m_myItem;
    int m_handle_;
    QPointF m_lastPos_;
    QPointF m_newPos_;
    bool m_bControled;
};


class RotateShapeCommand : public QUndoCommand
{
public:
    RotateShapeCommand(QGraphicsItem *item , const qreal oldAngle ,
                QUndoCommand * parent = 0);
    void undo() Q_DECL_OVERRIDE;
    void redo() Q_DECL_OVERRIDE;
private:
    QGraphicsItem *m_myItem;
    qreal m_myOldAngle;
    qreal m_newAngle;
};

class RemoveShapeCommand : public QUndoCommand
{
public:
    explicit RemoveShapeCommand(QGraphicsScene *graphicsScene, QUndoCommand *parent = 0);
    ~RemoveShapeCommand();
    void undo() Q_DECL_OVERRIDE;
    void redo() Q_DECL_OVERRIDE;

private:
    QList<QGraphicsItem *> m_items;
    QGraphicsScene *m_myGraphicsScene;
};

class GroupShapeCommand : public QUndoCommand
{
public:
    explicit GroupShapeCommand( QGraphicsItemGroup * group, QGraphicsScene *graphicsScene,
                           QUndoCommand *parent = 0);
    void undo() Q_DECL_OVERRIDE;
    void redo() Q_DECL_OVERRIDE;
private:
    QList<QGraphicsItem *> m_sitems;
    QGraphicsItemGroup * m_myGroup;
    QGraphicsScene *m_myGraphicsScene;
    bool m_b_undo;
};

class UnGroupShapeCommand : public QUndoCommand
{
public:
    explicit UnGroupShapeCommand( QGraphicsItemGroup * group, QGraphicsScene *graphicsScene,
                             QUndoCommand *parent = 0);
    void undo() Q_DECL_OVERRIDE;
    void redo() Q_DECL_OVERRIDE;
private:
    QList<QGraphicsItem *> m_items;
    QGraphicsItemGroup * m_myGroup;
    QGraphicsScene *m_myGraphicsScene;
};

class AddShapeCommand : public QUndoCommand
{
public:
    AddShapeCommand(QGraphicsItem *item , QGraphicsScene *graphicsScene,
               QUndoCommand *parent = 0);
    ~AddShapeCommand();

    void undo() Q_DECL_OVERRIDE;
    void redo() Q_DECL_OVERRIDE;

private:
    QGraphicsItem *m_myDiagramItem;
    QGraphicsScene *m_myGraphicsScene;
    QPointF m_initialPosition;
};

QString createCommandString(QGraphicsItem *item, const QPointF &point);


#endif // DTUNDOCOMMAND_H
