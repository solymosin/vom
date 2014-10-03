#ifndef VONAL_H
#define VONAL_H

#include <QGraphicsPixmapItem>
#include "node.h"

class vonalB : public QGraphicsLineItem {

public:
    vonalB(double x1, double y1, double x2, double y2, QGraphicsItem *parent = 0);

private:
    QLineF egyenes;
};

#endif // VONAL_H

