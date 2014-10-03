#ifndef NODE_H
#define NODE_H

#include <QGraphicsPixmapItem>

class node : public QGraphicsPolygonItem {

public:
    node(QGraphicsItem *parent = 0);

private:
    QPolygonF nodePoly;

};

#endif // NODE_H
