#ifndef KOR_H
#define KOR_H

#include <QGraphicsItem>

class kor : public QGraphicsPolygonItem {
public:
    kor(double w, QColor c, QGraphicsItem *parent = 0);
    QString nev;
};

#endif // KOR_H


