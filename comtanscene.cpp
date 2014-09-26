#include <QtGui>
//#include <QDeclarativeProperty>
#include <QGraphicsSceneMouseEvent>

#include "comtanscene.h"
#include "node.h"
#include "kor.h"
#include "vonal.h"

//! [0]
comtanScene::comtanScene(QObject *parent) : QGraphicsScene(parent){
//    myLineColor = Qt::black;
}


void comtanScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent){
    if (mouseEvent->button() != Qt::LeftButton)
        return;

    switch (kijeloltGomb){
        case 1:
            nod = new node();
            nod->setData(0,"pont");
            addItem(nod);
            nod->setPos(mouseEvent->scenePos());
//            qDebug() << mouseEvent->scenePos().x() << mouseEvent->scenePos().y();
            emit itemInserted(nod);
            break;
        case 2:
            circ = new kor();
            circ->setData(0,"circle");
            addItem(circ);
            circ->setPos(mouseEvent->scenePos());
            emit itemInserted2(circ);
            break;
        case 3:
            vonal = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(), mouseEvent->scenePos()));
            vonal->setPen(QPen(Qt::yellow, 2));
            addItem(vonal);
            emit itemInsertedV(vonal);
            break;
        default:
            ;
    }

//    qDebug() << kijeloltGomb;
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void comtanScene::addKor(double x, double y, qreal s, QString d){
    circ = new kor();
    circ->setData(0,"circle");
    circ->setData(1, d);
    addItem(circ);
    circ->setPos(x,y);
    circ->setScale(s);
    if(d=="TibiaCirc"){
        QPen pen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        circ->setPen(pen);
    }
    emit itemInserted2(circ);
}

void comtanScene::addKorB(double x, double y, qreal s){
    circ = new kor();
    circ->setData(0,"circle");
    addItem(circ);
    circ->setPos(x,y);
    circ->setScale(1);
    circ->update(x,y,s,s);
    emit itemInserted2(circ);
}


void comtanScene::addPont(double x, double y, QString d){
    nod = new node();
    nod->setData(0,"pont");
    nod->setData(1, d);
    addItem(nod);
    nod->setPos(x,y);
    emit itemInserted(nod);
}

void comtanScene::addPontB(double x, double y){
    nod = new node();
    nod->setData(0,"pont");
    addItem(nod);
    nod->setPos(x,y);
    QPen pen(Qt::yellow, 1);
    nod->setPen(pen);
    emit itemInserted(nod);
}

void comtanScene::addVonalB(double x1, double y1, double x2, double y2, QColor qc){
    if (x1<x2){
        vo = new vonalB(x1, y1, x2, y2);
        addItem(vo);
        vo->setLine(x1, y1, x2, y2);
    } else {
        vo = new vonalB(x2, y2, x1, y1);
        addItem(vo);
        vo->setLine(x2, y2, x1, y1);
    }
//    nod->setData(0,"pont");
    //addItem(vo);
    //vo->setLine(x1, y1, x2, y2);
    QPen pen(qc, 1.5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    vo->setPen(pen);
    emit itemInserted3(vo);
}

void comtanScene::setVonal(){
    QGraphicsLineItem *l = qgraphicsitem_cast<QGraphicsLineItem *>(selectedItems().first());
    QPen pen(Qt::red, 2.5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    l->setPen(pen);
}



//void comtanScene::wheelEvent(QGraphicsSceneWheelEvent *event){

//}

////    double uS = 50.0 / 100.0;
////    QMatrix oM = ui->graphicsView->matrix();
////    ui->graphicsView->resetMatrix();
////    ui->graphicsView->translate(oM.dx(), oM.dy());
////    ui->graphicsView->scale(uS,uS);

//}

void comtanScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent){
    if (kijeloltGomb == 3 && vonal != 0) {
        QLineF v(vonal->line().p1(), mouseEvent->scenePos());
        vonal->setLine(v);
    } else {
        QGraphicsScene::mouseMoveEvent(mouseEvent);
    }
//    else if (myMode == MoveItem) {
//        QGraphicsScene::mouseMoveEvent(mouseEvent);
//    }
}

void comtanScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent){
    if (kijeloltGomb == 3 && vonal != 0) {
        readPixDist(vonal->line().length());
//        removeItem(vonal);
//        delete vonal;
    }
    vonal = 0;
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

void comtanScene::gombKijelol(int i){
    kijeloltGomb = i;
}

void comtanScene::readPixDist(double dist){
    dPix = dist;
//    qDebug() << dPix;
}




