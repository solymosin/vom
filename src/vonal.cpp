#include <QtGui>
#include <QPainter>

#include "vonal.h"
#include "node.h"

vonalB::vonalB(double x1, double y1, double x2, double y2, QGraphicsItem *parent) : QGraphicsLineItem(parent){

    egyenes = QLineF(x1, y1, x2, y2);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
//    setPen(QPen(Qt::yellow, 0.3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    setOpacity(0.5);
}


//Arrow::Arrow(DiagramItem *startItem, DiagramItem *endItem,
//         QGraphicsItem *parent, QGraphicsScene *scene)
//    : QGraphicsLineItem(parent, scene)
//{
//    myStartItem = startItem;
//    myEndItem = endItem;
//    setFlag(QGraphicsItem::ItemIsSelectable, true);
//    myColor = Qt::black;
//    setPen(QPen(myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
//}

//node::node(QGraphicsItem *parent, QGraphicsScene *scene): QGraphicsPolygonItem(parent, scene){
//    nodePoly << QPointF(-5, -1) << QPointF(-5, 1)
//             << QPointF(-1, 1) << QPointF(-1, 5)
//             << QPointF(1, 5) << QPointF(1, 1)
//             << QPointF(5, 1) << QPointF(5, -1)
//             << QPointF(1, -1) << QPointF(1, -5)
//             << QPointF(-1, -5) << QPointF(-1, -1) << QPointF(-5, -1);

//    setPolygon(nodePoly);
//    setFlag(QGraphicsItem::ItemIsMovable, true);
//    setFlag(QGraphicsItem::ItemIsSelectable, true);
//    setBrush(Qt::red);
////    setOpacity(0.8);
//}
