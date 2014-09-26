#include <QtGui>
#include <QPainter>

#include "kor.h"

kor::kor(QGraphicsItem *parent): QGraphicsPolygonItem(parent){
    QRectF rect(-30.0, -30.0, 60.0, 60.0);

    QGraphicsEllipseItem *m_ellipse;
    m_ellipse = new QGraphicsEllipseItem(rect);

    setPolygon(m_ellipse->shape().toFillPolygon());
    setFlag(QGraphicsItem::ItemIsMovable, true);

    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setPen(QPen(Qt::yellow, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    setOpacity(0.6);
}

