#include <QtGui>
#include <QPainter>

#include "kor.h"

kor::kor(double w, QColor c, QGraphicsItem *parent): QGraphicsPolygonItem(parent){
    QRectF rect(-300.0, -300.0, 600.0, 600.0);

    QGraphicsEllipseItem *m_ellipse;
    m_ellipse = new QGraphicsEllipseItem(rect);
    setPolygon(m_ellipse->shape().toFillPolygon());

    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    QPen zz;
    zz.setColor(c);
    zz.setWidthF(w);
    zz.setCapStyle(Qt::FlatCap);
    zz.setJoinStyle(Qt::RoundJoin);
    setPen(zz);
    setOpacity(0.6);
}
