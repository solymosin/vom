#ifndef COMTANSCENE_H
#define COMTANSCENE_H

#include <QGraphicsScene>
#include <QObject>

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
class QMenu;
class QPointF;
class QGraphicsLineItem;
class QFont;
class QGraphicsTextItem;
class QColor;
QT_END_NAMESPACE

#include "node.h"
#include "kor.h"
#include "vonal.h"

class comtanScene: public QGraphicsScene{

    Q_OBJECT

public:
    comtanScene(QObject *parent=0);
    int kijeloltGomb;
    double dPix;
    QGraphicsTextItem *lab;

public slots:
    void gombKijelol(int i);
    void readPixDist(double dist);
    //void addKor(double x, double y, qreal s, QString d);
    void addKor(double x, double y, double d, double w, QColor c);
    void addKorB(double x, double y, qreal s, double w, QColor c, double ptx);
    void addPont(double x, double y, QString d);
    void addPontB(double x, double y);
    void addVonalB(double x1, double y1, double x2, double y2, QColor qc, double w);
    //void setVonal();

signals:
    void itemInserted(node *item);
    void itemInserted2(kor *item);
    void itemInserted3(vonalB *item);
    void itemInsertedV(QGraphicsLineItem *item);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
//    void wheelEvent(QGraphicsSceneWheelEvent *event);

private:
    node *nod;
    kor *circ;
    vonalB *vo;
    QGraphicsLineItem *vonal;
};

#endif // COMTANSCENE_H
