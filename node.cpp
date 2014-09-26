#include <QtGui>
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsPolygonItem>

#include "node.h"

node::node(QGraphicsItem *parent): QGraphicsPolygonItem(parent){
    nodePoly << QPointF(-5, -1) << QPointF(-5, 1)
             << QPointF(-1, 1) << QPointF(-1, 5)
             << QPointF(1, 5) << QPointF(1, 1)
             << QPointF(5, 1) << QPointF(5, -1)
             << QPointF(1, -1) << QPointF(1, -5)
             << QPointF(-1, -5) << QPointF(-1, -1) << QPointF(-5, -1);

    setPolygon(nodePoly);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setBrush(Qt::red);
    setOpacity(0.8);
}


